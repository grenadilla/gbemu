#include "memory.h"
#include "utils.h"

#include <iostream>

uint8_t Memory::get_IE() const {
    return interrupt_enable;
}

uint8_t Memory::get_IF() const {
    return interrupt_flag;
}

void Memory::set_IE(uint8_t value) {
    interrupt_enable = value;
}

void Memory::set_IF(uint8_t value) {
    interrupt_flag = value;
}

void Memory::update_timers(unsigned cycles) {
    timer.div_fill += cycles;

    if (timer.running) {
        timer.counter_fill += cycles;
    }

    if (timer.div_fill >= utils::DIV_TIMER_THRESHOLD) {
        // Increment div
        timer.divider++;
        timer.div_fill -= utils::DIV_TIMER_THRESHOLD;
    }

    unsigned timer_threshold = utils::TIMER_THRESHOLDS[timer.speed];
    if (timer.counter_fill >= timer_threshold) {
        // Increment counter
        timer.counter++;
        if (timer.counter == 0) {
            // Interrupt!
            interrupt_flag |= 0x04;
            timer.counter = timer.modulo;
        }
        timer.counter_fill -= timer_threshold;
    }
}

uint8_t Memory::get_timer_control() const {
    return (timer.unused << 3) | (timer.running << 2) | timer.speed;
}

void Memory::set_timer_control(uint8_t val) {
    timer.speed = val & 0x3;
    timer.running = val & 0x4;
    timer.unused = val & 0x8;
}

uint8_t Memory::hardware_read(uint16_t address) const {
    // TODO IO registers
    if (address == 0xFF04) {
        // Divider
        return timer.divider;
    } else if (address == 0xFF05) {
        return timer.counter;   
    } else if (address == 0xFF06) {
        return timer.modulo; 
    } else if (address == 0xFF07) {
        return get_timer_control(); 
    } else if (address == 0xFF0F) {
        // Interrupt Flag
        return interrupt_flag;
    } else if (address == 0xFFFF) {
        // Interrupt Enable
        return interrupt_enable; 
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
        timer.divider = 0;
    } else if (address == 0xFF05) {
        timer.counter = value;
    } else if (address == 0xFF06) {
        timer.modulo = value;
    } else if (address == 0xFF07) {
        set_timer_control(value); 
    } else if (address == 0xFF0F) {
        // Interrupt Flag
        interrupt_flag = value;
    } else if (address == 0xFFFF) {
        // Interrupt Enable
        interrupt_enable = value;
    } 
}