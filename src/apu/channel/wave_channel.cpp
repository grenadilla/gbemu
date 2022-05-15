#include "wave_channel.h"

void WaveChannel::set_wave_ram(uint16_t address, uint8_t value) {
    wave_ram[address] = value;
}

uint8_t WaveChannel::get_wave_ram(uint16_t address) const {
    return wave_ram[address];
}

float WaveChannel::sample_channel() const {
    if (!channel_enabled) {
        return 0;
    }
    return current_sample;
}

void WaveChannel::tick_channel() {
    frequency_timer -= 1;
    if (frequency_timer == 0) {
        frequency_timer = (2048 - frequency) * 2;
        wave_position = (wave_position + 1) % 32;

        uint8_t sample_byte = wave_ram[wave_position / 2];

        unsigned sample;
        if (wave_position % 2 == 0) {
            // Upper
            sample = (sample_byte & 0xF0) >> 4;
        } else {
            // Lower
            sample = sample_byte & 0x0F;
        }

        // Volume shift
        if (volume_shift == 0) {
            sample = 0;
        } else {
            sample >>= volume_shift - 1;
        }

        current_sample = sample;
    }
}

void WaveChannel::set_nrx0(uint8_t value) {
    channel_enabled = (value & 0x80) != 0;
}

uint8_t WaveChannel::get_nrx0() const {
    return channel_enabled << 7;
}

void WaveChannel::set_nrx1(uint8_t value) {
    length_data = value;
    length_counter = 264 - length_data;
}

uint8_t WaveChannel::get_nrx1() const {
    return length_data;
}

void WaveChannel::set_nrx2(uint8_t value) {
    volume_shift = (value & 0x60) >> 5;
}

uint8_t WaveChannel::get_nrx2() const {
    return volume_shift << 5;
}
