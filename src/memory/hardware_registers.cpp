#include "memory.h"

#include "utils.h"

#include <iostream>

uint8_t Memory::hardware_read(uint16_t address) const {
    // TODO IO registers
    switch(address) {
        case 0xFF04:
            return timer->get_divider();
        case 0xFF05:
            return timer->get_counter();
        case 0xFF06:
            return timer->get_modulo();
        case 0xFF07:
            return timer->get_control();
        case 0xFF0F:
            return interrupts->get_IF();
        case 0xFF40:
            return ppu->read_lcd_control();
        case 0xFF41:
            return ppu->read_stat();
        case 0xFF42:
            return ppu->get_scroll_y();
        case 0xFF43:
            return ppu->get_scroll_x();
        case 0xFF44:
            return ppu->get_ly();
        case 0xFF45:
            return ppu->get_lyc();
        case 0xFF47:
            return ppu->read_palette();
        case 0xFF4A:
            return ppu->get_window_y();
        case 0xFF4B:
            return ppu->get_window_x();
        case 0xFFFF:
            return interrupts->get_IE();
        default:
            return 0xFF;
    }
}

void Memory::hardware_write(uint16_t address, uint8_t value) {
    // TODO IO registers
    switch (address) {
        case 0xFF01:
            // Serial port
            // output character here for blargg's test roms
            std::cerr << (char) value;
            break;
        case 0xFF04:
            timer->set_divider(value);
            break;
        case 0xFF05:
            timer->set_counter(value);
            break;
        case 0xFF06:
            timer->set_modulo(value);
            break;
        case 0xFF07:
            timer->set_control(value);
            break;
        case 0xFF0F:
            interrupts->set_IF(value);
            break;
        case 0xFF40:
            ppu->write_lcd_control(value);
            break;
        case 0xFF41:
            ppu->write_stat(value);
            break;
        case 0xFF42:
            ppu->set_scroll_y(value);
            break;
        case 0xFF43:
            ppu->set_scroll_x(value);
            break;
        case 0xFF45:
            ppu->set_lyc(value);
            break;
        case 0xFF47:
            ppu->write_palette(value);
            break;
        case 0xFF4A:
            ppu->set_window_y(value);
            break;
        case 0xFF4B:
            ppu->set_window_x(value);
            break;
        case 0xFFFF:
            interrupts->set_IE(value);
            break;
    }
}