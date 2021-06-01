#pragma once

#include "interrupts.h"

#include <cstdint>
#include <ostream>

class Timer {
    public:
        Timer(Interrupts* interrupts);
        
        uint8_t get_timer_control() const;
        void set_timer_control(uint8_t val);
        void update_timers(unsigned cycles);
        void timer_debug(std::ostream& out);

        uint8_t get_divider() const;
        void set_divider(uint8_t val);

        uint8_t get_modulo() const;
        void set_modulo(uint8_t val);

        uint8_t get_counter() const;
        void set_counter(uint8_t val);
    private:
        // Note: DIV is implemented internally as uint16_t,
        // DIV register is upper 8 bits
        // Divider starts at this value after boot ROM
        uint16_t divider = 0xABCC;
        uint8_t counter;
        uint8_t modulo;
        // 00: 4096Hz, 01: 262144Hz, 10: 65536Hz, 11: 16384Hz
        uint8_t speed;
        bool running;

        Interrupts* interrupts;
};