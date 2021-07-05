#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "interrupts.h"
#include "timer.h"
#include "memory.h"
#include "cpu.h"

class Gameboy {
    public:
        Gameboy(std::string rom_path);
        ~Gameboy();
        void run(bool debug = false);

    private:
        void tick(CPU& cpu);
        void print_help();
        void init_graphics();
        void debug_run(CPU& cpu);

        Interrupts interrupts;
        Timer timer;
        PPU ppu;
        Memory* mem;
        bool quit = false;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
};