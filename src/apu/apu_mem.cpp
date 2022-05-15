#include "apu.h"

void APU::set_nr21(uint8_t value) {
    c2_duty_number = (value & 0xC0) >> 6;
    c2_length_data = value & 0x3F;
    c2_length_counter = 64 - c2_length_data;
}

uint8_t APU::get_nr21() const {
    return (c2_duty_number << 6) | c2_length_data;
}

void APU::set_nr22(uint8_t value) {
    c2_initial_volume = (value & 0xF0) >> 4;
    c2_volume_increase = (value & 0x08) != 0;

    // TODO figure out if we need another variable to store this
    // instead of using period variable
    c2_envelope_period = value & 0x07;
}

uint8_t APU::get_nr22() const {
    return (c2_initial_volume << 4) | (c2_volume_increase << 3) | c2_envelope_period;
}

void APU::set_nr23(uint8_t value) {
    c2_frequency &= 0x0700;
    c2_frequency |= value;
}

uint8_t APU::get_nr23() const {
    return c2_frequency & 0x00FF;
}

void APU::set_nr24(uint8_t value) {
    uint16_t freq_high_bits = (value & 0x07) << 8;
    c2_frequency &= 0x00FF;
    c2_frequency |= freq_high_bits;

    c2_length_enable = (value & 0x40) != 0;

    if ((value & 0x80) != 0) {
        // Restart sound
        trigger_c2();
    }
}

uint8_t APU::get_nr24() const {
    uint8_t freq_high_bits = (c2_frequency & 0xF0) >> 8;
    return (c2_length_enable << 6) | freq_high_bits;
}

void APU::set_nr50(uint8_t value) {
    nr50 = value;
}

uint8_t APU::get_nr50() const {
    return nr50;
}