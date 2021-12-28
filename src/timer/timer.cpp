#include "timer.h"

#include "utils.h"
#include <iomanip>

Timer::Timer(Interrupts* interrupts) : interrupts(interrupts) { }

uint8_t Timer::get_divider() const {
    // Divider register is upper 8 bits
    return (divider & 0xFF00) >> 8;
}

void Timer::set_divider(uint8_t val) {
    // Depending on speed and bit, switching from high to low
    // will still increment the timer
    if ((speed == 0 && (divider & 0x0200))
        || (speed == 1 && (divider & 0x0008))
        || (speed == 2 && (divider & 0x0020))
        || (speed == 3 && (divider & 0x0080))) {
        counter++;
    }

    divider = 0;
}

uint8_t Timer::get_modulo() const {
    return modulo;
}

void Timer::set_modulo(uint8_t val) {
    modulo = val;
}

uint8_t Timer::get_counter() const {
    return counter;
}

void Timer::set_counter(uint8_t val) {
    counter = val;
}

void Timer::update_timers(unsigned cycles) {
    // See detailed schematics: https://gbdev.io/pandocs/Timer_Obscure_Behaviour.html

    // Falling edge detection
    // TODO simplify and make more efficient
    for (unsigned i = 0; i < cycles; i += 4) {
        bool previous_div_bit = 0;
        switch (speed) {
            case 0:
                previous_div_bit = divider & 0x0200;
                break;
            case 1:
                previous_div_bit = divider & 0x0008;
                break;
            case 2:
                previous_div_bit = divider & 0x0020;
                break;
            case 3:
                previous_div_bit = divider & 0x0080;
        }

        divider += 4;

        bool next_div_bit = 0;
        switch (speed) {
            case 0:
                next_div_bit = divider & 0x0200;
                break;
            case 1:
                next_div_bit = divider & 0x0008;
                break;
            case 2:
                next_div_bit = divider & 0x0020;
                break;
            case 3:
                next_div_bit = divider & 0x0080;
        }

        bool previous = previous_div_bit & running;
        bool after = next_div_bit & running;

        if (previous && !after) {
            counter++;
            if (counter == 0) {
                // Interrupt!
                interrupts->set_interrupt(Interrupts::TIMER);
                counter = modulo;
            }
        }
    }
}

uint8_t Timer::get_control() const {
    uint8_t result = 0xF8 | ((uint8_t) running << 2) | speed;
    return result;
}

void Timer::set_control(uint8_t val) {
    speed = val & 0x3;
    running = val & 0x4;
}

void Timer::timer_debug(std::ostream& out) {
    unsigned clocks = 1024;
    switch (speed) {
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

    out << "0xFF04 (Divider) : " << utils::hexify16 << divider << '\n'
        << "0xFF05 (Counter) : " << utils::hexify8 << +counter << '\n'
        << "0xFF06 (Modulo)  : " << utils::hexify8 << +modulo << '\n'
        << "0xFF07 (Control) : " << utils::hexify8 << +get_control() << '\n'
        << "Speed: " << std::dec << clocks << ", Running: " << running 
        << '\n' << std::endl;
}
