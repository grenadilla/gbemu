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

    channel1.tick_channel();
    channel2.tick_channel();
    channel3.tick_channel();

    sample_counter -= 1;
    if (sample_counter == 0) {
        sample_counter = utils::CLOCK_SPEED / utils::AUDIO_FREQUENCY;
        sample_sound();
    }
}

void APU::tick_fs() {
    frame_sequencer_timer -= 1;
    if (frame_sequencer_timer == 0) {
        frame_sequencer_timer = utils::FRAME_SEQUENCER_PERIOD;
        frame_sequencer_step = (frame_sequencer_step + 1) % 8;

        if (frame_sequencer_step % 2 == 0) {
            // Length ctrl on 0, 2, 4, 6, makes 256hz
            channel1.tick_length();
            channel2.tick_length();
            channel3.tick_length();
        }
        if (frame_sequencer_step == 7) {
            channel1.tick_envelope();
            channel2.tick_envelope();
        }
        if (frame_sequencer_step == 2 || frame_sequencer_step == 6) {
            channel1.tick_sweep();
        }
    }
}

void APU::sample_sound() {
    if (audio_device == 0) {
        return;
    }

    float result = 0.0;

    float input = (channel1.sample_channel() + channel2.sample_channel() + channel3.sample_channel()) / 100;
    input /= 3;
    SDL_MixAudioFormat((Uint8*) &result, (Uint8*) &input, AUDIO_F32SYS, sizeof(float), SDL_MIX_MAXVOLUME);

    sound_queue.push_back(result);
}

void APU::queue_sound() {
    if (sound_queue.size() == 0) {
        return;
    }

    SDL_QueueAudio(audio_device, sound_queue.data(), sizeof(float) * sound_queue.size());
    sound_queue.clear();
}

bool APU::queue_full() {
    return sound_queue.size() >= utils::AUDIO_BUFFER_SIZE / sizeof(float) - 128;
}