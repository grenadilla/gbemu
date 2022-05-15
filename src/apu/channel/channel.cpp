#include "channel.h"

void Channel::tick_envelope() {
    // Tick channel 2 envelope
    if (envelope_period != 0) {
        if (envelope_period_timer > 0) {
            envelope_period_timer -= 1;
        }

        if (volume_enabled && envelope_period_timer == 0) {
            envelope_period_timer = envelope_period;
            if (current_volume < 15 && volume_increase) {
                current_volume += 1;
            }
            else if (current_volume > 0 && !volume_increase) {
                current_volume -= 1;
            } else {
                volume_enabled = false;
            }
        }
    }
}

void Channel::tick_length() {
    if (length_enable) {
        length_counter -= 1;
        if (length_counter == 0) {
            //c2_length_counter = 64 - c2_length_data;
            channel_enabled = false;
        }
    }
}

void Channel::tick_channel() {
    frequency_timer -= 1;
    if (frequency_timer == 0) {
        frequency_timer = (2048 - frequency) * 4;
        wave_position = (wave_position + 1) % 8;
    }
}

void Channel::trigger_channel() {
    channel_enabled = true;
    volume_enabled = true;
    frequency_timer = (2048 - frequency) * 4;
    envelope_period_timer = envelope_period;
    current_volume = initial_volume;
}

float Channel::sample_channel() const {
    if (!channel_enabled) {
        return 0;
    }
    unsigned dac_input = WAVE_PATTERN[duty_number][wave_position] * current_volume;
    // Shift to range between 0 and 128
    return (128 * dac_input) / 7;
}