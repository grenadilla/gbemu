#pragma once

#include "memory.h"

#include <vector>
#include <cstdint>

class MBC0 : public Memory {
    public:
        MBC0(const std::vector<uint8_t>& rom_data, Interrupts*, Timer* timer, PPU* ppu, Joypad* joypad);

        void print_debug() {}

    private:
        uint8_t mbc_read(const uint16_t address) const;
        void mbc_write(const uint16_t address, uint8_t value);

        uint8_t ram_read(uint16_t offset) const;
        void ram_write(uint16_t offset, uint8_t value);
};
