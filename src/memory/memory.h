#pragma once

#include "timer.h"
#include "interrupts.h"
#include "ppu.h"
#include "utils.h"

#include <string>
#include <vector>
#include <cstdint>

class Memory {
    public:
        Memory(const std::string rom_path, Interrupts* interrupts, Timer* new_timer, PPU* ppu);
        virtual ~Memory() {}
        uint8_t read(uint16_t address, bool debug = false) const;
        void write(uint16_t address, uint8_t value);
        bool is_loaded() const;

    protected:
        // The address used for rom_read and rom_write
        // are relative to the ROM, not the memory map
        // In practicality this is ptr - 0x4000
        virtual uint8_t rom_read(uint16_t address) const = 0;
        virtual void rom_write(uint16_t address, uint8_t value) = 0;

        uint8_t hardware_read(uint16_t address) const;
        void hardware_write(uint16_t address, uint8_t value);

        std::vector<uint8_t> rom_data;
        uint8_t ext_ram[8 * utils::KILOBYTE];
        uint8_t wram0[4 * utils::KILOBYTE];
        uint8_t wram1[4 * utils::KILOBYTE];
        uint8_t sprite_attr_table[160];
        uint8_t hram[126];

    private:
        Interrupts* interrupts;
        Timer* timer;
        PPU* ppu;
};

class MBC0 : public Memory {
    public:
        MBC0(const std::string rom_path, Interrupts*, Timer* timer, PPU* ppu);
        uint8_t rom_read(const uint16_t address) const;
        void rom_write(const uint16_t address, uint8_t value);
};
