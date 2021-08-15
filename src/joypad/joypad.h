#pragma once

#include "interrupts.h"
#include <cstdint>
#include <SDL2/SDL.h>

class Joypad {
    public:
        Joypad(Interrupts* interrupts);
        void parse_key_event(SDL_Event event);
        void write_joypad(uint8_t value);
        uint8_t read_joypad();

    private:
        Interrupts* interrupts;
        bool action;
        bool direction;

        bool start;
        bool select;
        bool button_b;
        bool button_a;

        bool down;
        bool up;
        bool left;
        bool right;
};