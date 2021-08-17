#include "mbc0.h"

#include <iostream>

MBC0::MBC0(const std::vector<uint8_t>& rom_data, Interrupts* interrupts, Timer* timer, PPU* ppu, Joypad* joypad) 
    : Memory(rom_data, interrupts, timer, ppu, joypad) {}

uint8_t MBC0::mbc_read(uint16_t address) const {
    if (address < 0x8000) {
        return rom_data[address];
    } else if (address >= 0xA000 && address < 0xC000) {
        std::cerr << "Invalid read into nonexistent external RAM" << std::endl;
    }
    return 0xFF;
}

void MBC0::mbc_write(uint16_t address, uint8_t value) {
    if (address < 0x8000) {
        std::cerr << "Attempted write into ROM of " << utils::hexify8 << +value 
            << " at address " << utils::hexify16 << address << std::endl;
    } else if (address >= 0xA000 && address < 0xC000) {
        std::cerr << "Invalid write into nonexistent external RAM" << std::endl;
    }
}