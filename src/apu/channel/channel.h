#pragma once

#include <cstdint>
#include "utils.h"

class Channel {
    public:
        void tick_envelope();
        void tick_length();
        void tick_sweep();
        void tick_channel();

        void trigger_channel();
        float sample_channel() const;

        // Channel 1 only
        void set_nrx0(uint8_t value);
        uint8_t get_nrx0() const;

        void set_nrx1(uint8_t value);
        uint8_t get_nrx1() const;

        void set_nrx2(uint8_t value);
        uint8_t get_nrx2() const;

        void set_nrx3(uint8_t value);
        uint8_t get_nrx3() const;

        void set_nrx4(uint8_t value);
        uint8_t get_nrx4() const;

    private:
        unsigned sweep_calculate_frequency();

        static constexpr short WAVE_PATTERN[4][8] = {
            {0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 0}
        };

    protected:
        bool channel_enabled = false;

        // Starts out as all 11 bits on
        uint16_t frequency = 2047;
        unsigned frequency_timer = 4;
        unsigned wave_position = 0;
        unsigned duty_number = 0;

        // LENGTH
        bool length_enable = false;
        uint8_t length_data = 0;
        unsigned length_counter = 64;

        // VOLUME
        // Ranges from 0 to 15
        bool volume_enabled = true;
        unsigned current_volume = 0;
        unsigned initial_volume = 0;
        bool volume_increase = false;
        // Ranges from 0 to 7
        unsigned envelope_period_timer = 0;
        unsigned envelope_period = 0;

        // SWEEP
        unsigned sweep_period = 7;
        bool sweep_increase = true;
        unsigned sweep_shift = 0;

        bool sweep_enabled = false;
        unsigned shadow_frequency = frequency;
        unsigned sweep_timer = sweep_period;
};