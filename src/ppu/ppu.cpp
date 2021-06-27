#include "ppu.h"

#include <iostream>
#include <string>

bool PPU::validate_vram_access(std::string source) {
    switch (status) {
        case SEARCH:
        case HBLANK:
        case VBLANK:
            return true;
        case READ:
            std::cerr << "Invalid " << source << "; current mode is" 
                << status << std::endl;
            return false;
    }
}

void PPU::write_tile_data(uint16_t address, uint8_t value) {
    if (validate_vram_access("tile data write")) {
        tile_data[address] = value;
    }
}

void PPU::write_tile_map1(uint16_t address, uint8_t value) {
    if (validate_vram_access("tile map 1 write")) {
        tile_map1[address] = value;
    }
}

void PPU::write_tile_map2(uint16_t address, uint8_t value) {
    if (validate_vram_access("tile map 2 write")) {
        tile_map2[address] = value;
    }
}

uint8_t PPU::read_tile_data(uint16_t address, bool debug) {
    if (debug || validate_vram_access("tile data read")) {
        return tile_data[address];
    }
    return 0xFF;
}

uint8_t PPU::read_tile_map1(uint16_t address, bool debug) {
    if (debug || validate_vram_access("tile map 1 read")) {
        return tile_map1[address];
    }
    return 0xFF;
}

uint8_t PPU::read_tile_map2(uint16_t address, bool debug) {
    if (debug || validate_vram_access("tile map 2 read")) {
        return tile_data[address];
    }
    return 0xFF;
}