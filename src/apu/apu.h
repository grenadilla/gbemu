#pragma once

#include <cstdint>
#include <SDL2/SDL.h>
#include "utils.h"

class APU {
    public:
        void run(unsigned cycles);
        void tick();

        void set_audio_device(SDL_AudioDeviceID id);

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
    
    private:
        void tick_fs();
        void tick_envelope();
        void tick_c2();

        void trigger_c2();
        float get_c2() const;

        static constexpr short WAVE_PATTERN[4][8] = {
            {0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 1, 1},
            {0, 0, 0, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 0}
        };

        // FRAME SEQUENCER
        unsigned frame_sequencer_timer = utils::FRAME_SEQUENCER_PERIOD;
        unsigned frame_sequencer_step = 0;

        // CHANNEL 2
        // Starts out as all 11 bits on
        uint16_t c2_frequency = 2047;
        unsigned c2_frequency_timer = 4;
        unsigned c2_wave_position = 0;
        unsigned c2_duty_number = 0;

        bool c2_counter_selection = false;

        // Ranges from 0 to 15
        unsigned c2_current_volume = 0;
        unsigned c2_initial_volume = 0;
        bool c2_volume_increase = false;
        // Ranges from 0 to 7
        unsigned c2_envelope_period_timer = 0;
        unsigned c2_envelope_period = 0;

        SDL_AudioDeviceID audio_device = 0;
        uint8_t nr50 = 0;
};