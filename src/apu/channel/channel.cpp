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

unsigned Channel::sweep_calculate_frequency() {
    unsigned new_frequency = shadow_frequency >> sweep_shift;
    if (sweep_increase) {
        new_frequency = shadow_frequency + new_frequency;
    } else {
        new_frequency = shadow_frequency - new_frequency;
    }

    if (new_frequency > 2047) {
        channel_enabled = false;
    }

    return new_frequency;
}

void Channel::tick_sweep() {
    sweep_timer -= 1;
    if (sweep_timer == 0) {
        sweep_timer = sweep_period == 0 ? 8 : sweep_period;

        if (sweep_enabled && sweep_period != 0) {
            unsigned new_frequency = sweep_calculate_frequency();
            if (new_frequency <= 2047 && sweep_shift != 0) {
                frequency = new_frequency;
                shadow_frequency = new_frequency;

                // Overflow check again
                sweep_calculate_frequency();
            }
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
    envelope_period_timer = envelope_period;
    current_volume = initial_volume;

    frequency_timer = (2048 - frequency) * 4;
    shadow_frequency = frequency;

    sweep_timer = sweep_period == 0 ? 8 : sweep_period;
    sweep_enabled = sweep_period != 0 || sweep_shift != 0;;
    if (sweep_shift != 0) {
        // Overflow check
        sweep_calculate_frequency();
    }
}

float Channel::sample_channel() const {
    if (!channel_enabled) {
        return 0;
    }
    unsigned dac_input = WAVE_PATTERN[duty_number][wave_position] * current_volume;
    // Shift to range between 0 and 128
    return dac_input;
}