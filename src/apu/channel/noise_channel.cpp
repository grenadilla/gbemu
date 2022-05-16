#include "noise_channel.h"

void NoiseChannel::set_nrx3(uint8_t value) {
    // Polynomial counter
    divisor_shift = (value & 0xF0) >> 4;
    counter_width_less = (value & 0x08) != 0;
    base_divisor_code = value & 0x07;
}

uint8_t NoiseChannel::get_nrx3() const {
    return (divisor_shift << 4) | (counter_width_less << 3) | base_divisor_code;
}

void NoiseChannel::tick_channel() {
    frequency_timer -= 1;
    if (frequency_timer == 0) {
        unsigned divisor = (base_divisor_code == 0 ? 8 : (base_divisor_code * 16));
        frequency_timer = divisor << divisor_shift;

        // XOR 0th and 1st bit
        uint16_t xored = (lfsr & 0b01) ^ ((lfsr & 0b10) >> 1);
        lfsr >>= 1;
        lfsr |= (xored << 14);

        if (counter_width_less) {
            // Store in bit 6
            lfsr &= 0b10111111;
            lfsr |= (xored << 6);
        }
    }
}

void NoiseChannel::trigger_channel() {
    channel_enabled = true;

    volume_enabled = true;
    envelope_period_timer = envelope_period;
    current_volume = initial_volume;

    // TODO reload frequency timer?
    unsigned divisor = (base_divisor_code == 0 ? 8 : (base_divisor_code * 16));
    frequency_timer = divisor << divisor_shift;

    if (length_counter == 0) {
        length_counter = 64;
    }

    lfsr = 0x7FFF;
}

float NoiseChannel::sample_channel() const {
    if (!channel_enabled) {
        return 0;
    }
    
    unsigned amplitude = ~lfsr & 0x01;
    return amplitude * current_volume;
}