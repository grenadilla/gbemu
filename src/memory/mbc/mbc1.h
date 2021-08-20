#pragma once

#include "memory.h"

#include "utils.h"
#include <vector>
#include <cstdint>
#include <fstream>

class MBC1 : public Memory {
    public:
        MBC1(const std::vector<uint8_t>& rom_data, Interrupts*, Timer* timer, PPU* ppu, Joypad* joypad);

    private:
        uint8_t rom_bank_number = 0x01;
        uint8_t ram_bank_number = 0x00;
        bool ram_enabled = false;
        bool rom_mode = true;
        unsigned ram_size = 8 * utils::KILOBYTE;

        std::ofstream save_file;

        uint8_t mbc_read(const uint16_t address) const;
        void mbc_write(const uint16_t address, uint8_t value);

        uint8_t ram_read(uint16_t offset) const;
        void ram_write(uint16_t offset, uint8_t value);
};
