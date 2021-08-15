#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "interrupts.h"
#include "timer.h"
#include "joypad.h"
#include "memory.h"
#include "cpu.h"

class Gameboy {
    public:
        Gameboy(std::string rom_path);
        ~Gameboy();
        void run(bool debug = false, bool tilemap = false);

    private:
        void tick(CPU& cpu);
        void print_help();
        void init_graphics(bool tilemap);
        void debug_run(CPU& cpu);

        Interrupts interrupts;
        Timer timer;
        Joypad joypad;
        PPU ppu;
        Memory* mem;
        bool quit = false;

        unsigned last_time = 0;
        unsigned tick_countdown = 0;
        unsigned cycle_acc = 0;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        SDL_Window* tile_window = nullptr;
        SDL_Renderer* tile_renderer = nullptr;
};