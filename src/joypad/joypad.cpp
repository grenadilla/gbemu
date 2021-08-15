#include "joypad.h"

#include <iostream>

Joypad::Joypad(Interrupts* interrupts) : interrupts(interrupts) { }

void Joypad::parse_key_event(SDL_Event event) {
    bool pressed = event.type == SDL_KEYDOWN;
    switch (event.key.keysym.sym) {
        case SDLK_a:
            button_b = pressed;
            break; 
        case SDLK_s:
            button_a = pressed;
            break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            select = pressed;
            break;
        case SDLK_RETURN:
            start = pressed;
            break;
        case SDLK_DOWN:
            down = pressed;
            break;
        case SDLK_UP:
            up = pressed;
            break;
        case SDLK_LEFT:
            left = pressed;
            break;
        case SDLK_RIGHT:
            right = pressed;
            break;
    }
}

void Joypad::write_joypad(uint8_t value) {
    action = !(value & 0x20);
    direction = !(value & 0x10);
}

uint8_t Joypad::read_joypad() {
    if (action) {
        return (!action << 5) | (1 << 4) | (!start << 3) | (!select << 2) | (!button_b << 1) | !button_a;
    }
    return (1 << 5) | (!direction << 4) | (!down << 3) | (!up << 2) | (!left << 1) | !right;
}