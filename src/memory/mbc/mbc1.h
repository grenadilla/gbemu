#pragma once

#include "memory.h"

#include <vector>
#include <cstdint>

class MBC1 : public Memory {
    public:
        MBC1(const std::vector<uint8_t>& rom_data, Interrupts*, Timer* timer, PPU* ppu, Joypad* joypad);
        uint8_t mbc_read(const uint16_t address) const;
        void mbc_write(const uint16_t address, uint8_t value);
    private:
        uint8_t rom_bank_number = 0x01;
        uint8_t ram_bank_number = 0x00;
        bool ram_enabled = false;
        bool rom_mode = true;
        uint8_t RAM[32 * utils::KILOBYTE] = {0};
};
