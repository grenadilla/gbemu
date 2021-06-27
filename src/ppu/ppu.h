#pragma once

#include "utils.h"

#include <cstdint>

constexpr int KILOBYTE = 1024;

class PPU {
    public:
        enum Mode {
            SEARCH = 2,
            READ = 3,
            HBLANK = 0,
            VBLANK = 1
        };

        void write_tile_data(uint16_t address, uint8_t value);
        void write_tile_map1(uint16_t address, uint8_t value);
        void write_tile_map2(uint16_t address, uint8_t value);

        // TODO add debug flag to allow debugger
        // to read data during any mode
        uint8_t read_tile_data(uint16_t address, bool debug = false);
        uint8_t read_tile_map1(uint16_t address, bool debug = false);
        uint8_t read_tile_map2(uint16_t address, bool debug = false);
    private:
        uint8_t tile_data[6 * utils::KILOBYTE];
        uint8_t tile_map1[utils::KILOBYTE];
        uint8_t tile_map2[utils::KILOBYTE];

        bool validate_vram_access(std::string source = "[UNKNOWN SOURCE]");

        Mode status = SEARCH;
};