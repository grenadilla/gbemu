#include "mbc1.h"

#include <iostream>

MBC1::MBC1(const std::vector<uint8_t>& rom_data, Interrupts* interrupts, Timer* timer, PPU* ppu, Joypad* joypad) 
    : Memory(rom_data, interrupts, timer, ppu, joypad) {
    RAM.resize(ram_size, 0);
}

uint8_t MBC1::mbc_read(uint16_t address) const {
    if (address < 0x4000) {
        return rom_data[address];
    } else if (address >= 0x4000 && address < 0x8000) {
        // ROM banks
        uint16_t offset = address - 0x4000;
        return rom_data[rom_bank_number * 16 * utils::KILOBYTE + offset];
    }
    return 0xFF;
}

void MBC1::mbc_write(uint16_t address, uint8_t value) {
    if (address < 0x2000) {
        ram_enabled = (value & 0x0F) == 0x0A;
        if (ram_enabled && RAM.size() < ram_size) {
            RAM.resize(ram_size, 0);
        } else {
            // Save RAM to disk
        }
    } else if (address >= 0x2000 && address < 0x4000) {
        // ROM bank number
        uint8_t bits = value & 0x1F;
        if (bits == 0) {
            bits++;
        }
        rom_bank_number &= 0xE0;
        rom_bank_number |= bits;
    } else if (address >= 0x4000 && address < 0x6000) {
        uint8_t bits = value & 0x03;
        if (rom_mode) {
            rom_bank_number &= 0x1F;
            rom_bank_number |= (bits << 6);
        } else {
            ram_bank_number = bits;
        }
    } else if (address >= 0x6000 && address < 0x8000) {
        rom_mode = !(value & 0x01);
        if (rom_mode) {
            ram_size = 8 * utils::KILOBYTE;
        } else {
            ram_size = 32 * utils::KILOBYTE;
        }
    }
}

uint8_t MBC1::ram_read(uint16_t offset) const {
    if (ram_enabled) {
        return RAM[ram_bank_number * 8 * utils::KILOBYTE + offset];
    }
    std::cerr << "Attempted to read RAM bank when RAM is disabled" << std::endl;
    return 0xFF;
}

void MBC1::ram_write(uint16_t offset, uint8_t value) {
    if (ram_enabled) {
        RAM[ram_bank_number * 8 * utils::KILOBYTE + offset] = value;
    } else {
        std::cerr << "Attempted to write into RAM bank when RAM is disabled" << std::endl;
    }
}