#include "joypad.h"

#include <iostream>

Joypad::Joypad(Interrupts* interrupts) : interrupts(interrupts) { }

void Joypad::parse_key_event(SDL_Event event) {
    bool pressed = event.type == SDL_KEYDOWN;
    switch (event.key.keysym.sym) {
        case SDLK_a:
            button_b = pressed;
            std::cout << "Button b " << (pressed ? "pressed" : "unpressed") << std::endl;
            break; 
        case SDLK_s:
            button_a = pressed;
            std::cout << "Button a " << (pressed ? "pressed" : "unpressed") << std::endl;
            break;
        case SDLK_LSHIFT:
        case SDLK_RSHIFT:
            select = pressed;
            std::cout << "Select " << (pressed ? "pressed" : "unpressed") << std::endl;
            break;
        case SDLK_RETURN:
            start = pressed;
            std::cout << "Start " << (pressed ? "pressed" : "unpressed") << std::endl;
            break;
        case SDLK_DOWN:
            down = pressed;
            std::cout << "Down " << (pressed ? "pressed" : "unpressed") << std::endl;
            break;
        case SDLK_UP:
            up = pressed;
            std::cout << "Up " << (pressed ? "pressed" : "unpressed") << std::endl;
            break;
        case SDLK_LEFT:
            left = pressed;
            std::cout << "Left " << (pressed ? "pressed" : "unpressed") << std::endl;
            break;
        case SDLK_RIGHT:
            right = pressed;
            std::cout << "Right " << (pressed ? "pressed" : "unpressed") << std::endl;
            break;
    }
}

void Joypad::write_joypad(uint8_t value) {
    action = value & 0x20;
    direction = value & 0x10;
}

uint8_t Joypad::read_joypad() {
    if (action) {
        return (action << 5) | (start << 3) | (select << 2) | (button_b << 1) | button_a;
    }
    return (direction << 4) | (down << 3) | (up << 2) | (left << 1) | right;
}