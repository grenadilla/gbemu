#include "memory.h"

#include "utils.h"

#include <iostream>

uint8_t Memory::hardware_read(uint16_t address) const {
    // TODO IO registers
    switch(address) {
        case 0xFF04:
            return timer->get_divider();
            break;
        case 0xFF05:
            return timer->get_counter();
            break;
        case 0xFF06:
            return timer->get_modulo();
            break;
        case 0xFF07:
            return timer->get_control();
            break;
        case 0xFF0F:
            return interrupts->get_IF();
            break;
        case 0xFFFF:
            return interrupts->get_IE();
            break;
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
        case 0xFFFF:
            interrupts->set_IE(value);
    }
}