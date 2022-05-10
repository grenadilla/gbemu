#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

class APU {
    public:
        void run(unsigned cycles);
        void tick();

        void set_audio_device(SDL_AudioDeviceID id);

        void set_nr50(uint8_t value);
        uint8_t get_nr50() const;
    
    private:
        SDL_AudioDeviceID audio_device = 0;
        uint8_t nr50 = 0;
};