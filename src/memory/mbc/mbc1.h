#pragma once

#include "memory.h"

#include "utils.h"
#include <vector>
#include <cstdint>
#include <fstream>

class MBC1 : public Memory {
    public:
        MBC1(const std::vector<uint8_t>& rom_data, unsigned num_banks, unsigned ram_size,
            Interrupts*, Timer* timer, PPU* ppu, Joypad* joypad);

        void print_debug() {}

    private:
        uint8_t bank1 = 0x01;
        uint8_t bank2 = 0x00;

        // For ROM sizes less than 2 megabytes, we need to mask off the
        // extra ROM bank bits that are unneeded
        uint8_t bank_mask = 0xFF;

        bool ram_enabled = false;
        bool rom_mode = true;

        unsigned ram_size = 0;

        std::ofstream save_file;

        void set_bank1(uint8_t bits);
        void set_bank2(uint8_t bits);

        uint8_t get_rom_bank(bool lower) const;
        uint8_t get_ram_bank() const;

        uint8_t mbc_read(const uint16_t address) const;
        void mbc_write(const uint16_t address, uint8_t value);

        uint8_t ram_read(uint16_t offset) const;
        void ram_write(uint16_t offset, uint8_t value);
};
