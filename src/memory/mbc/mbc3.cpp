#include "mbc3.h"

#include <iostream>

MBC3::MBC3(const std::vector<uint8_t>& rom_data, unsigned num_banks, unsigned ram_size,
    Interrupts* interrupts, Timer* timer, PPU* ppu, Joypad* joypad) 
    : Memory(rom_data, interrupts, timer, ppu, joypad) {
    std::ifstream file(title + ".sav", std::ios::in | std::ios::binary);
    if (file.is_open()) {
        RAM = std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), 
            std::istreambuf_iterator<char>());
    } else {
        RAM.resize(ram_size * utils::KILOBYTE, 0);
    }

    this->ram_size = ram_size;

    // Calculate number of ROM banks and form the mask
    // each bank is 16 kilobytes
    bank_mask = num_banks == 0 ? 1 : num_banks - 1;
}

uint8_t MBC3::mbc_read(uint16_t address) const {
    if (address < 0x4000) {
        return rom_data[address];
    } else if (address >= 0x4000 && address < 0x8000) {
        // ROM banks
        uint16_t offset = address - 0x4000;
        return rom_data[rom_bank_number * 16 * utils::KILOBYTE + offset];
    }
    return 0xFF;
}

void MBC3::mbc_write(uint16_t address, uint8_t value) {
    if (address < 0x2000) {
        bool previous = ram_enabled;
        ram_enabled = (value & 0x0F) == 0x0A;
        if (previous && !ram_enabled) {
            // Turned RAM off, so save RAM to disk as save file
            if (!save_file.is_open()) {
                save_file = std::ofstream(title + ".sav", std::ios::out | std::ios::binary);
            }
            save_file.write(((char*) RAM.data()), ram_size * utils::KILOBYTE);
            save_file.seekp(0);
            std::cout << "Saving " << title << ".sav" << std::endl;
        }
    } else if (address >= 0x2000 && address < 0x4000) {
        // ROM bank number
        uint8_t bits = value & 0x7F & bank_mask;
        if (bits == 0) {
            rom_bank_number = 1;
        } else {
            rom_bank_number = bits;
        }
    } else if (address >= 0x4000 && address < 0x6000) {
        if (value <= 0x03) {
            ram_bank_number = value;
        } else if (value >= 0x08 && value <= 0x0C) {
            // RTC registers
        }
    } else if (address >= 0x6000 && address < 0x8000) {
        
    }
}

uint8_t MBC3::ram_read(uint16_t offset) const {
    if (ram_enabled) {
        return RAM[ram_bank_number * 8 * utils::KILOBYTE + offset];
    }
    std::cerr << "Attempted to read RAM bank when RAM is disabled" << std::endl;
    return 0xFF;
}

void MBC3::ram_write(uint16_t offset, uint8_t value) {
    if (ram_enabled) {
        RAM[ram_bank_number * 8 * utils::KILOBYTE + offset] = value;
    } else {
        std::cerr << "Attempted to write into RAM bank when RAM is disabled" << std::endl;
    }
}

void MBC3::print_debug() {
    std::cout << "Ram enabled: " << (int) ram_enabled << '\n'
    << "RTC Mode: " << (int) rtc_mode << '\n'
    << "Rom Bank: " << (int) rom_bank_number << '\n'
    << "Ram Bank: " << (int) ram_bank_number << '\n' << std::endl;
}