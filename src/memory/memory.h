#pragma once

#include "timer.h"
#include "interrupts.h"
#include "ppu.h"
#include "joypad.h"
#include "utils.h"

#include <string>
#include <vector>
#include <cstdint>

class Memory {
    public:
        static Memory* get_cartridge(const std::string& rom_path, Interrupts* interrupts, Timer* new_timer, PPU* ppu, Joypad* joypad);
        Memory(const std::vector<uint8_t>& rom_data, Interrupts* interrupts, Timer* new_timer, PPU* ppu, Joypad* joypad);
        virtual ~Memory() {}
        uint8_t read(uint16_t address, bool transfer = false, bool debug = false) const;
        void write(uint16_t address, uint8_t value);
        bool is_loaded() const;

        // Used for DMA transfer to OAM cycle counting
        void tick(unsigned cycles);

    protected:
        std::string title;
        
        bool ram_enabled = false;
        std::vector<uint8_t> RAM;

        std::vector<uint8_t> rom_data;
        uint8_t wram0[4 * utils::KILOBYTE];
        uint8_t wram1[4 * utils::KILOBYTE];
        uint8_t hram[126];

        // If 0, not in OAM transfer
        // otherwise is number of cycles left in transfer
        unsigned OAM_countdown = 0;
        uint16_t OAM_base = 0x00;

    private:
        Interrupts* interrupts;
        Timer* timer;
        PPU* ppu;
        Joypad* joypad;

        virtual uint8_t mbc_read(uint16_t address) const = 0;
        virtual void mbc_write(uint16_t address, uint8_t value) = 0;

        // Unlike the other read and write functions which go off address,
        // RAM read/write functions go off offset from beginning of RAM address space
        virtual uint8_t ram_read(uint16_t offset) const = 0;
        virtual void ram_write(uint16_t offset, uint8_t value) = 0;

        uint8_t hardware_read(uint16_t address) const;
        void hardware_write(uint16_t address, uint8_t value);
};
