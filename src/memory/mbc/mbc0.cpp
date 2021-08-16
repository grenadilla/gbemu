#include "mbc0.h"

MBC0::MBC0(const std::vector<uint8_t>& rom_data, Interrupts* interrupts, Timer* timer, PPU* ppu, Joypad* joypad) 
    : Memory(rom_data, interrupts, timer, ppu, joypad) {}

uint8_t MBC0::rom_read(uint16_t address) const {
    return rom_data[address];
}

void MBC0::rom_write(uint16_t address, uint8_t value) {
    std::cerr << "Attempted write into ROM of " << utils::hexify8 << +value 
        << " at address " << utils::hexify16 << address << std::endl;
}