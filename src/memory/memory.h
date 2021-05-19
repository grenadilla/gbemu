#pragma once

#include <string>
#include <vector>
#include <cstdint>

constexpr int KILOBYTE = 1024;

class Memory {
    public:
        Memory(const std::string rom_path);
        virtual ~Memory() {}
        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);
        bool is_loaded() const;
        uint8_t get_IE() const;
        uint8_t get_IF() const;
        void set_IE(uint8_t value);
        void set_IF(uint8_t value);
    protected:
        // The address used for rom_read and rom_write
        // are relative to the ROM, not the memory map
        // In practicality this is ptr - 0x4000
        virtual uint8_t rom_read(uint16_t address) const = 0;
        virtual void rom_write(uint16_t address, uint8_t value) = 0;

        std::vector<uint8_t> rom_data;
        uint8_t vram[8 * KILOBYTE];
        uint8_t ext_ram[8 * KILOBYTE];
        uint8_t wram0[4 * KILOBYTE];
        uint8_t wram1[4 * KILOBYTE];
        uint8_t sprite_attr_table[160];
        uint8_t hram[126];
        uint8_t interrupt_enable;
        uint8_t interrupt_flag;
};

class MBC0 : public Memory {
    public:
        MBC0(const std::string rom_path);
        uint8_t rom_read(const uint16_t address) const;
        void rom_write(const uint16_t address, uint8_t value);
};
