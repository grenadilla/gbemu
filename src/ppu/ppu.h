#pragma once

#include "utils.h"

#include <cstdint>

constexpr int KILOBYTE = 1024;

class PPU {
    public:
        void write_tile_data(uint16_t address, uint8_t value);
        void write_tile_map1(uint16_t address, uint8_t value);
        void write_tile_map2(uint16_t address, uint8_t value);

        // TODO add debug flag to allow debugger
        // to read data during any mode
        uint8_t read_tile_data(uint16_t address, bool debug = false);
        uint8_t read_tile_map1(uint16_t address, bool debug = false);
        uint8_t read_tile_map2(uint16_t address, bool debug = false);

        void write_lcd_control(uint8_t value);
        uint8_t read_lcd_control();

        void set_scroll_y(uint8_t value);
        void set_scroll_x(uint8_t value);
        void set_lyc(uint8_t value);
        void set_window_y(uint8_t value);
        void set_window_x(uint8_t value);

        uint8_t get_scroll_y();
        uint8_t get_scroll_x();
        uint8_t get_ly();
        uint8_t get_lyc();
        uint8_t get_window_y();
        uint8_t get_window_x();

        void write_stat(uint8_t value);
        uint8_t read_stat();

        void write_palette(uint8_t value);
        uint8_t read_palette();

    private:
        enum Mode {
            SEARCH = 2,
            READ = 3,
            HBLANK = 0,
            VBLANK = 1,
        };

        enum Interrupt_Source {
            LYC_STAT = 0x40,
            OAM_STAT = 0x20,
            VBLANK_STAT = 0x10,
            HBLANK_STAT = 0x08,
        };

        enum Color {
            WHITE = 0,
            LIGHT_GREY = 1,
            DARK_GREY = 2,
            BLACK = 3
        };

        // TODO set color data to map to rgb
        // constexpr COLORS[4] = {...}

        uint8_t tile_data[6 * utils::KILOBYTE];
        uint8_t tile_map1[utils::KILOBYTE];
        uint8_t tile_map2[utils::KILOBYTE];

        // LCD control
        bool lcd_enable;
        bool window_map; // false - 0x9800-0x9BFF, true - 0x9C00 - 0x9FFF
        bool window_enable;
        bool tile_data_area; // false - 0x8800-0x9700, true 0x8000-0x8FFF
        bool bg_map; // false - 0x9800-0x9BFF, true - 0x9C00 - 0x9FFF
        bool obj_size; // false - 8x8, true - 8x16
        bool obj_enable;
        bool bg_window_enable;

        uint8_t scroll_y;
        uint8_t scroll_x;
        uint8_t ly;
        uint8_t lyc;
        uint8_t window_y;
        uint8_t window_x;

        Interrupt_Source stat_interrupt = LYC_STAT;
        Mode status = SEARCH;
        Color bg_palette[4];

        bool validate_vram_access(std::string source = "[UNKNOWN SOURCE]");
};