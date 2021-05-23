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
    // See detailed schematics: https://gbdev.io/pandocs/Timer_Obscure_Behaviour.html

    // Falling edge detection
    bool previous_div_bit = 0;
    switch (timer.speed) {
        case 0:
            previous_div_bit = timer.divider & 0x0200;
            break;
        case 1:
            previous_div_bit = timer.divider & 0x0008;
            break;
        case 2:
            previous_div_bit = timer.divider & 0x0020;
            break;
        case 3:
            previous_div_bit = timer.divider & 0x0080;
    }

    timer.divider += cycles;

    bool next_div_bit = 0;
    switch (timer.speed) {
        case 0:
            next_div_bit = timer.divider & 0x0200;
            break;
        case 1:
            next_div_bit = timer.divider & 0x0008;
            break;
        case 2:
            next_div_bit = timer.divider & 0x0020;
            break;
        case 3:
            next_div_bit = timer.divider & 0x0080;
    }

    bool previous = previous_div_bit & timer.running;
    bool after = next_div_bit & timer.running;

    if (previous && !after) {
        timer.counter++;
        if (timer.counter == 0) {
            // Interrupt!
            interrupt_flag |= 0x04;
            timer.counter = timer.modulo;
        }
    }
}

uint8_t Memory::get_timer_control() const {
    uint8_t result = 0xF8 | ((uint8_t) timer.running << 2) | timer.speed;
    return result;
}

void Memory::set_timer_control(uint8_t val) {
    timer.speed = val & 0x3;
    timer.running = val & 0x4;
}

void Memory::timer_debug(std::ostream& out) {
    unsigned clocks = 1024;
    switch (timer.speed) {
        case 0:
            clocks = 1024;
            break;
        case 1:
            clocks = 16;
            break;
        case 2:
            clocks = 64;
            break;
        case 3:
            clocks = 256;
            break;
    }

    out << "0xFF04 (Divider) : " << utils::hexify16 << timer.divider << '\n'
        << "0xFF05 (Counter) : " << utils::hexify8 << +timer.counter << '\n'
        << "0xFF06 (Modulo)  : " << utils::hexify8 << +timer.modulo << '\n'
        << "0xFF07 (Control) : " << utils::hexify8 << +get_timer_control() << '\n'
        << "Speed: " << std::dec << clocks << ", Running: " << timer.running 
        << '\n' << std::endl;
}

uint8_t Memory::hardware_read(uint16_t address) const {
    // TODO IO registers
    if (address == 0xFF04) {
        // Divider register is upper 8 bits
        return (timer.divider & 0xF0) >> 8;
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