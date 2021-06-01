#include "memory.h"

#include "utils.h"

#include <iostream>

uint8_t Memory::hardware_read(uint16_t address) const {
    // TODO IO registers
    if (address == 0xFF04) {
        return timer->get_divider();
    } else if (address == 0xFF05) {
        return timer->get_counter();
    } else if (address == 0xFF06) {
        return timer->get_modulo();
    } else if (address == 0xFF07) {
        return timer->get_timer_control(); 
    } else if (address == 0xFF0F) {
        // Interrupt Flag
        return interrupts->get_interrupt_flags();
    } else if (address == 0xFFFF) {
        // Interrupt Enable
        return interrupts->get_interrupt_enable();
    } 
    return 0xFF;
}

void Memory::hardware_write(uint16_t address, uint8_t value) {
    // TODO IO registers
    if (address == 0xFF01) {
        // Serial port
        // output character here for blargg's test roms
        std::cerr << (char) value;
    } else if (address == 0xFF04) {
        timer->set_divider(value);
    } else if (address == 0xFF05) {
        timer->set_counter(value);
    } else if (address == 0xFF06) {
        timer->set_modulo(value);
    } else if (address == 0xFF07) {
        timer->set_timer_control(value); 
    } else if (address == 0xFF0F) {
        // Interrupt Flag
        interrupts->set_interrupt_flags(value);
    } else if (address == 0xFFFF) {
        // Interrupt Enable
        interrupts->set_interrupt_enable(value);
    } 
}