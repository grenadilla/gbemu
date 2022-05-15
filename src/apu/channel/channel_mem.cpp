#include "channel.h"

void Channel::set_nrx0(uint8_t value) {
    sweep_period = (value & 0xE0) >> 5;
    sweep_increase = (value & 0x08) == 0;
    sweep_shift = value & 0x07;
}

uint8_t Channel::get_nrx0() const {
    return (sweep_period << 5) | (sweep_increase << 3) | sweep_shift;
}

void Channel::set_nrx1(uint8_t value) {
    duty_number = (value & 0xC0) >> 6;
    length_data = value & 0x3F;
    length_counter = 64 - length_data;
}

uint8_t Channel::get_nrx1() const {
    return (duty_number << 6) | length_data;
}

void Channel::set_nrx2(uint8_t value) {
    initial_volume = (value & 0xF0) >> 4;
    volume_increase = (value & 0x08) != 0;

    // TODO figure out if we need another variable to store this
    // instead of using period variable
    envelope_period = value & 0x07;
}

uint8_t Channel::get_nrx2() const {
    return (initial_volume << 4) | (volume_increase << 3) | envelope_period;
}

void Channel::set_nrx3(uint8_t value) {
    frequency &= 0x0700;
    frequency |= value;
}

uint8_t Channel::get_nrx3() const {
    return frequency & 0x00FF;
}

void Channel::set_nrx4(uint8_t value) {
    uint16_t freq_high_bits = (value & 0x07) << 8;
    frequency &= 0x00FF;
    frequency |= freq_high_bits;

    length_enable = (value & 0x40) != 0;

    if ((value & 0x80) != 0) {
        // Restart sound
        trigger_channel();
    }
}

uint8_t Channel::get_nrx4() const {
    uint8_t freq_high_bits = (frequency & 0xF0) >> 8;
    return (length_enable << 6) | freq_high_bits;
}