#include "apu.h"
#include <iostream>

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

    sample_counter -= 1;
    if (sample_counter == 0) {
        sample_counter = utils::CLOCK_SPEED / utils::AUDIO_FREQUENCY;
        buffer_sound();
    }
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
    // Shift to range between 0 and 128
    return (128 * dac_input) / 7;
}

void APU::buffer_sound() {
    if (audio_device == 0) {
        return;
    }

    float channel2 = get_c2();
    float result = 0.0;
    //Sint32 result = channel2 * utils::AUDIO_AMPLITUDE;
    SDL_MixAudioFormat((Uint8*) &result, (Uint8*) &channel2, AUDIO_F32SYS, sizeof(float), utils::AUDIO_AMPLITUDE);
    sound_queue.push_back(result);
}

void APU::queue_sound() {
    if (sound_queue.size() == 0) {
        //std::cout << "Empty queue!" << std::endl;
        return;
    }

    //std::cout << "Queue!" << std::endl;

    SDL_QueueAudio(audio_device, sound_queue.data(), sizeof(float) * sound_queue.size());
    sound_queue.clear();
}

bool APU::queue_full() {
    return sound_queue.size() > utils::AUDIO_BUFFER_SIZE / sizeof(float);
}