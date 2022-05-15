#pragma once

#include <cstdint>
#include "channel.h"

class WaveChannel : public Channel {
    public:
        float sample_channel() const;
        void tick_channel();
        void trigger_channel();

        void set_nrx0(uint8_t value);
        uint8_t get_nrx0() const;

        void set_nrx1(uint8_t value);
        uint8_t get_nrx1() const;

        void set_nrx2(uint8_t value);
        uint8_t get_nrx2() const;

        void set_wave_ram(uint16_t address, uint8_t value);
        uint8_t get_wave_ram(uint16_t address) const;

    private:
        uint8_t wave_ram[16] = { 0 };
        unsigned volume_shift = 0;

        unsigned current_sample = 0;

        bool playback = false;
};