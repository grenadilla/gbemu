#include "apu.h"

void APU::set_audio_device(SDL_AudioDeviceID id) {
    audio_device = id;
}

void APU::run(unsigned cycles) {
    for (unsigned i = 0; i < cycles; i++) {
        tick();
    }
}

void APU::tick() {
    tick_fs();
    tick_c2();
}

void APU::tick_fs() {
    frame_sequencer_timer -= 1;
    if (frame_sequencer_timer == 0) {
        frame_sequencer_timer = utils::FRAME_SEQUENCER_PERIOD;
        frame_sequencer_step = (frame_sequencer_step + 1) % 8;

        if (frame_sequencer_step % 2 == 0) {
            // Length ctrl on 0, 2, 4, 6, makes 256hz
        }
        if (frame_sequencer_step == 7) {
            tick_envelope();
        }
        if (frame_sequencer_step == 2 || frame_sequencer_step == 6) {

        }
    }
}

void APU::tick_envelope() {
    // Tick channel 2 envelope
    if (c2_envelope_period != 0) {
        if (c2_envelope_period_timer > 0) {
            c2_envelope_period_timer -= 1;
        }

        if (c2_envelope_period_timer == 0) {
            c2_envelope_period_timer = c2_envelope_period;
            if (c2_current_volume < 0xF && c2_volume_increase) {
                c2_current_volume += 1;
            }
            else if (c2_current_volume > 0x0 && !c2_volume_increase) {
                c2_current_volume -= 1;
            }
        }
    }
}

void APU::tick_c2() {
    c2_frequency_timer -= 1;
    if (c2_frequency_timer == 0) {
        c2_frequency_timer = (2048 - c2_frequency) * 4;
        c2_wave_position = (c2_wave_position + 1) % 8;
    }
}

void APU::trigger_c2() {
    c2_envelope_period_timer = c2_envelope_period;
    c2_current_volume = c2_initial_volume;
}

float APU::get_c2() const {
    unsigned dac_input = WAVE_PATTERN[c2_duty_number][c2_wave_position] * c2_current_volume;
    return (dac_input / 7.5) - 1.0;
}