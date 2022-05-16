#pragma once

#include "channel.h"
#include <cstdint>

class NoiseChannel : public Channel {
    public:
        void set_nrx3(uint8_t value);
        uint8_t get_nrx3() const;

        void set_nrx4(uint8_t value);
        uint8_t get_nrx4() const;

        void tick_channel();
        void trigger_channel();
        float sample_channel() const;

    private:
        unsigned divisor_shift = 0;
        bool counter_width_less = false;
        unsigned base_divisor_code = 0;

        // Linear feedback shift register
        uint16_t lfsr = 0;
};