#pragma once

#include <cstdint>
#include <vector>
#include <SDL2/SDL.h>
#include "utils.h"
#include "channel.h"

class APU {
    public:
        void run(unsigned cycles);
        void tick();

        void set_audio_device(SDL_AudioDeviceID id);

        void set_nr10(uint8_t value);
        uint8_t get_nr10() const;

        void set_nr11(uint8_t value);
        uint8_t get_nr11() const;

        void set_nr12(uint8_t value);
        uint8_t get_nr12() const;

        void set_nr13(uint8_t value);
        uint8_t get_nr13() const;

        void set_nr14(uint8_t value);
        uint8_t get_nr14() const;

        void set_nr21(uint8_t value);
        uint8_t get_nr21() const;

        void set_nr22(uint8_t value);
        uint8_t get_nr22() const;

        void set_nr23(uint8_t value);
        uint8_t get_nr23() const;

        void set_nr24(uint8_t value);
        uint8_t get_nr24() const;

        void set_nr50(uint8_t value);
        uint8_t get_nr50() const;

        void queue_sound();
        bool queue_full();
    
    private:
        // Glorious sound!
        void sample_sound();

        void tick_fs();

        std::vector<float> sound_queue;

        unsigned sample_counter = utils::CLOCK_SPEED / utils::AUDIO_FREQUENCY;

        static constexpr short WAVE_PATTERN[4][8] = {
            {0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 0}
        };

        // FRAME SEQUENCER
        unsigned frame_sequencer_timer = utils::FRAME_SEQUENCER_PERIOD;
        unsigned frame_sequencer_step = 0;

        Channel channel1;
        Channel channel2;

        SDL_AudioDeviceID audio_device = 0;
        uint8_t nr50 = 0;
};