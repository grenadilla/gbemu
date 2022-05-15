#include "apu.h"

void APU::set_nr21(uint8_t value) {
    // TODO set up length function
    c2_duty_number = (value & 0xC0) >> 6;
}

uint8_t APU::get_nr21() const {
    // TODO set up length function
    return (c2_duty_number << 6);
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
    c2_frequency &= 0xF0;
    c2_frequency |= value;
}

uint8_t APU::get_nr23() const {
    return c2_frequency & 0x0F;
}

void APU::set_nr24(uint8_t value) {
    uint16_t freq_high_bits = (value & 0x07) << 8;
    c2_frequency &= 0x0F;
    c2_frequency |= freq_high_bits;

    // TODO figure out length function, bit 6
    c2_counter_selection = (value & 0x40) != 0;

    if ((value & 0x80) != 0) {
        // Restart sound
        trigger_c2();
    }
}

uint8_t APU::get_nr24() const {
    uint8_t freq_high_bits = (c2_frequency & 0xF0) >> 8;
    return (c2_counter_selection << 6) | freq_high_bits;
}

void APU::set_nr50(uint8_t value) {
    nr50 = value;
}

uint8_t APU::get_nr50() const {
    return nr50;
}