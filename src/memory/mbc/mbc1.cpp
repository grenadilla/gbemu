#include "mbc1.h"
#include "utils.h"

#include <iostream>

MBC1::MBC1(const std::vector<uint8_t>& rom_data, unsigned num_banks, unsigned ram_size, 
    Interrupts* interrupts, Timer* timer, PPU* ppu, Joypad* joypad) 
    : Memory(rom_data, interrupts, timer, ppu, joypad) {
    std::ifstream file(title + ".sav", std::ios::in | std::ios::binary);
    if (file.is_open()) {
        /*RAM = std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), 
            std::istreambuf_iterator<char>());*/
    } else {
        RAM.resize(ram_size * utils::KILOBYTE, 0);
    }

    this->ram_size = ram_size;

    // Calculate number of ROM banks and form the mask
    // each bank is 16 kilobytes
    bank_mask = num_banks - 1;
}

void MBC1::set_bank1(uint8_t bits) {
    bank1 = bits & 0x1F;
    if (bank1 == 0) {
        bank1 = 1;
    }
}

void MBC1::set_bank2(uint8_t bits) {
    bank2 = bits & 0x03;
}

uint8_t MBC1::get_rom_bank(bool lower) const {
    if (lower) {
        if (rom_mode) {
            return 0;
        } else {
            return (bank2 << 5) & bank_mask;
        }
    } else {
        return ((bank2 << 5) | bank1) & bank_mask;
    }
}

uint8_t MBC1::get_ram_bank() const {
    if (rom_mode || ram_size < 32) {
        return 0;
    }
    return bank2;
}

uint8_t MBC1::mbc_read(uint16_t address) const {
    uint8_t bank;
    uint16_t offset;
    if (address < 0x4000) {
        bank = get_rom_bank(true);
        offset = address;
    } else if (address >= 0x4000 && address < 0x8000) {
        bank = get_rom_bank(false);
        offset = address - 0x4000;
    } else {
        return 0xFF;
    }

    return rom_data[bank * 16 * utils::KILOBYTE + offset];
}

void MBC1::mbc_write(uint16_t address, uint8_t value) {
    if (address < 0x2000) {
        bool previous = ram_enabled;
        ram_enabled = (value & 0x0F) == 0x0A;
        if (!previous && ram_enabled) {
            std::cout << "Enable RAM" << std::endl;
        }
        
        if (previous && !ram_enabled) {
            // Turned RAM off, so save RAM to disk as save file
            /*if (!save_file.is_open()) {
                save_file = std::ofstream(title + ".sav", std::ios::out | std::ios::binary);
            }
            save_file.write(((char*) RAM.data()), ram_size * utils::KILOBYTE);
            save_file.seekp(0);
            std::cerr << "Saving " << title << ".sav" << std::endl;*/
            std::cout << "Disable RAM" << std::endl;
        }
    } else if (address >= 0x2000 && address < 0x4000) {
        set_bank1(value);
    } else if (address >= 0x4000 && address < 0x6000) {
        set_bank2(value);
    } else if (address >= 0x6000 && address < 0x8000) {
        rom_mode = !(value & 0x01);
    }
}

uint8_t MBC1::ram_read(uint16_t offset) const {
    if (ram_enabled) {
        return RAM[get_ram_bank() * 8 * utils::KILOBYTE + offset];
    }
    //std::cerr << "Attempted to read RAM bank when RAM is disabled" << std::endl;
    return 0xFF;
}

void MBC1::ram_write(uint16_t offset, uint8_t value) {
    if (ram_enabled) {
        RAM[get_ram_bank() * 8 * utils::KILOBYTE + offset] = value;
    } else {
        //std::cerr << "Attempted to write into RAM bank when RAM is disabled" << std::endl;
    }
}