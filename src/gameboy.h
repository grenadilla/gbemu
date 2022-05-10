#pragma once

#include <string>
#include <SDL2/SDL.h>

#include "interrupts.h"
#include "timer.h"
#include "joypad.h"
#include "memory.h"
#include "apu.h"
#include "ppu.h"
#include "cpu.h"

class Gameboy {
    public:
        Gameboy(std::string rom_path);
        ~Gameboy();
        void run(bool debug = false, bool graphics = true, bool tilemap = false, bool sound = true);

    private:
        void tick(CPU& cpu);
        void print_help();

        void init_sdl();
        void shutdown_sdl();

        void debug_run(CPU& cpu);

        Interrupts interrupts;
        Timer timer;
        Joypad joypad;
        APU apu;
        PPU ppu;
        Memory* mem;
        bool quit = false;

        unsigned last_time = 0;
        unsigned tick_countdown = 0;
        unsigned cycle_acc = 0;

        // use_video == use_graphics || use_tilemap
        bool use_video;
        bool use_graphics;
        bool use_tilemap;
        bool use_audio;

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        SDL_Window* tile_window = nullptr;
        SDL_Renderer* tile_renderer = nullptr;

        SDL_AudioDeviceID audio_device = 0;
};