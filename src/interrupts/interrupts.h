#pragma once

#include <cstdint>

class Interrupts {
    public:
        // Interrupt flags
        static constexpr uint8_t VBLANK = 0x01;
        static constexpr uint8_t LCD_STAT = 0x02;
        static constexpr uint8_t TIMER = 0x04;
        static constexpr uint8_t SERIAL = 0x08;
        static constexpr uint8_t JOYPAD = 0x10;

        uint8_t get_IF() const;
        void set_IF(uint8_t value);

        uint8_t get_IE() const;
        void set_IE(uint8_t value);

        void enable_interrupts();
        void disable_interrupts();
        bool get_IME() const;

        uint8_t get_interrupt();

        void set_interrupt(uint8_t flag);

        void print_debug();

    private:
        uint8_t interrupt_enable = 0;
        uint8_t interrupt_flags = 0xE1;

        // EI is delayed - see https://gbdev.gg8.se/wiki/articles/Interrupts
        bool ime_delay = false;
        bool ime = false;
};