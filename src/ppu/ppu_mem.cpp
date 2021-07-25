#include "ppu.h"

#include <iostream>
#include <string>

bool PPU::validate_vram_access(std::string source) {
    if (!lcd_enable) {
        return true;
    }
    switch (status) {
        case OAM_SEARCH:
        case HBLANK:
        case VBLANK:
            return true;
        case READ:
            std::cerr << "Invalid " << source << "; current mode is " 
                << status << std::endl;
            return false;
    }
}

void PPU::write_tile_data(uint16_t address, uint8_t value) {
    if (validate_vram_access("tile data write")) {
        tile_data[address] = value;

        // Update debug tile map display
        draw_tile_display(address);
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

void PPU::write_lcd_control(uint8_t value) {
    lcd_enable = value & 0x80;
    window_map = value & 0x40;
    window_enable = value & 0x20;
    tile_data_area = value & 0x10;
    bg_map = value & 0x08;
    obj_size = value & 0x04;
    obj_enable = value & 0x02;
    bg_window_enable = value & 0x01;
}

uint8_t PPU::read_lcd_control() {
    return (lcd_enable << 7)
            | (window_map << 6)
            | (window_enable << 5)
            | (tile_data_area << 4)
            | (bg_map << 3)
            | (obj_size << 2)
            | (obj_enable << 1)
            | bg_window_enable;
}

void PPU::set_scroll_y(uint8_t value) {
    scroll_y = value;
}

void PPU::set_scroll_x(uint8_t value) {
    scroll_x = value;
}

void PPU::set_lyc(uint8_t value) {
    lyc = value;
}

void PPU::set_window_y(uint8_t value) {
    window_y = value;
}

void PPU::set_window_x(uint8_t value) {
    window_x = value;
}

uint8_t PPU::get_scroll_y() {
    return scroll_y;
}

uint8_t PPU::get_scroll_x() {
    return scroll_x;
}

uint8_t PPU::get_ly() {
    return ly;
}

uint8_t PPU::get_lyc() {
    return lyc;
}

uint8_t PPU::get_window_y() {
    return window_y;
}

uint8_t PPU::get_window_x() {
    return window_x;
}

void PPU::write_stat(uint8_t value) {
    stat_interrupt = static_cast<Interrupt_Source>(value & 0x78);
    status = static_cast<Mode>(value & 0x03);
}

uint8_t PPU::read_stat() {
    return static_cast<uint8_t>(stat_interrupt)
        | ((lyc == ly) << 2)
        | static_cast<uint8_t>(status);
}

void PPU::write_palette(uint8_t value) {
    bg_palette[3] = static_cast<Color>((value & 0xC0) >> 6);
    bg_palette[2] = static_cast<Color>((value & 0x30) >> 4);
    bg_palette[1] = static_cast<Color>((value & 0x0C) >> 2);
    bg_palette[0] = static_cast<Color>(value & 0x03);

    // For debug
    update_all_tile_display();
}

uint8_t PPU::read_palette() {
    return (static_cast<uint8_t>(bg_palette[3]) << 6)
        | (static_cast<uint8_t>(bg_palette[2]) << 4)
        | (static_cast<uint8_t>(bg_palette[1]) << 2)
        | static_cast<uint8_t>(bg_palette[0]);
}