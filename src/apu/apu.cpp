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
    channel4.tick_channel();

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
            channel4.tick_length();
        }
        if (frame_sequencer_step == 7) {
            channel1.tick_envelope();
            channel2.tick_envelope();
            channel4.tick_envelope();
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

    float left = 0.0;
    float right = 0.0;

    if (apu_on) {
        int raw_input = 0;
        int num_channels = 0;
        int channel_volume = 0;
        float input;

        // Mix left
        if (c4_left) {
            raw_input += channel4.sample_channel();
            num_channels++;
        }

        if (c3_left) {
            raw_input += channel3.sample_channel();
            num_channels++;
        }

        if (c2_left) {
            raw_input += channel2.sample_channel();
            num_channels++;
        }

        if (c1_left) {
            raw_input += channel1.sample_channel();
            num_channels++;
        }

        channel_volume = left_volume + 1;

        if (num_channels > 0) {
            input = (raw_input / 4.0) / 10.0;
        } else {
            input = 0.0;
        }

        SDL_MixAudioFormat((Uint8*) &left, (Uint8*) &input, AUDIO_F32SYS, utils::AUDIO_CHANNEL_SAMPLE_SIZE, channel_volume * 16);

        raw_input = 0;
        num_channels = 0;

        // Mix right
        if (c4_right) {
            raw_input += channel4.sample_channel();
            num_channels++;
        }

        if (c3_right) {
            raw_input += channel3.sample_channel();
            num_channels++;
        }

        if (c2_right) {
            raw_input += channel2.sample_channel();
            num_channels++;
        }

        if (c1_right) {
            raw_input += channel1.sample_channel();
            num_channels++;
        }

        channel_volume = right_volume + 1;

        if (num_channels > 0) {
            input = (raw_input / 4.0) / 10.0;
        } else {
            input = 0.0;
        }

        SDL_MixAudioFormat((Uint8*) &right, (Uint8*) &input, AUDIO_F32SYS, utils::AUDIO_CHANNEL_SAMPLE_SIZE, channel_volume * 16);
    }

    sound_queue.push_back(left);
    sound_queue.push_back(right);
}

void APU::queue_sound() {
    if (sound_queue.size() == 0) {
        return;
    }

    SDL_QueueAudio(audio_device, sound_queue.data(), utils::AUDIO_CHANNEL_SAMPLE_SIZE * sound_queue.size());
    sound_queue.clear();
}

bool APU::queue_full() {
    return sound_queue.size() >= utils::AUDIO_BUFFER_SIZE / utils::AUDIO_SAMPLE_SIZE;
}