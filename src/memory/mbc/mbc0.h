#pragma once

#include "memory.h"

#include <vector>
#include <cstdint>

class MBC0 : public Memory {
    public:
        MBC0(const std::vector<uint8_t>& rom_data, Interrupts*, Timer* timer, PPU* ppu, Joypad* joypad);
        uint8_t rom_read(const uint16_t address) const;
        void rom_write(const uint16_t address, uint8_t value);
};
