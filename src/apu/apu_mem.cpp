#include "apu.h"

void APU::set_nr10(uint8_t value) {
    channel1.set_nrx0(value);
}

uint8_t APU::get_nr10() const {
    return channel1.get_nrx0();
}

void APU::set_nr11(uint8_t value) {
    channel1.set_nrx1(value);
}

uint8_t APU::get_nr11() const {
    return channel1.get_nrx1();
}

void APU::set_nr12(uint8_t value) {
    channel1.set_nrx2(value);
}

uint8_t APU::get_nr12() const {
    return channel1.get_nrx2();
}

void APU::set_nr13(uint8_t value) {
    channel1.set_nrx3(value);
}

uint8_t APU::get_nr13() const {
    return channel1.get_nrx3();
}

void APU::set_nr14(uint8_t value) {
    channel1.set_nrx4(value);
}

uint8_t APU::get_nr14() const {
    return channel1.get_nrx4();
}

void APU::set_nr21(uint8_t value) {
    channel2.set_nrx1(value);
}

uint8_t APU::get_nr21() const {
    return channel2.get_nrx1();
}

void APU::set_nr22(uint8_t value) {
    channel2.set_nrx2(value);
}

uint8_t APU::get_nr22() const {
    return channel2.get_nrx2();
}

void APU::set_nr23(uint8_t value) {
    channel2.set_nrx3(value);
}

uint8_t APU::get_nr23() const {
    return channel2.get_nrx3();
}

void APU::set_nr24(uint8_t value) {
    channel2.set_nrx4(value);
}

uint8_t APU::get_nr24() const {
    return channel2.get_nrx4();
}

void APU::set_nr30(uint8_t value) {
    channel3.set_nrx0(value);
}

uint8_t APU::get_nr30() const {
    return channel3.get_nrx0();
}

void APU::set_nr31(uint8_t value) {
    channel3.set_nrx1(value);
}

uint8_t APU::get_nr31() const {
    return channel3.get_nrx1();
}

void APU::set_nr32(uint8_t value) {
    channel3.set_nrx2(value);
}

uint8_t APU::get_nr32() const {
    return channel3.get_nrx2();
}

void APU::set_nr33(uint8_t value) {
    channel3.set_nrx3(value);
}

uint8_t APU::get_nr33() const {
    return channel3.get_nrx3();
}

void APU::set_nr34(uint8_t value) {
    channel3.set_nrx4(value);
}

uint8_t APU::get_nr34() const {
    return channel3.get_nrx4();
}

void APU::set_wave_ram(uint16_t address, uint8_t value) {
    channel3.set_wave_ram(address, value);
}

uint8_t APU::get_wave_ram(uint16_t address) {
    return channel3.get_wave_ram(address);
}

void APU::set_nr41(uint8_t value) {
    channel4.set_nrx1(value);
}

uint8_t APU::get_nr41() const {
    return channel4.get_nrx1();
}

void APU::set_nr42(uint8_t value) {
    channel4.set_nrx2(value);
}

uint8_t APU::get_nr42() const {
    return channel4.get_nrx2();
}

void APU::set_nr43(uint8_t value) {
    channel4.set_nrx3(value);
}

uint8_t APU::get_nr43() const {
    return channel4.get_nrx3();
}

void APU::set_nr44(uint8_t value) {
    channel4.set_nrx4(value);
}

uint8_t APU::get_nr44() const {
    return channel4.get_nrx4();
}

void APU::set_nr50(uint8_t value) {
    left_vin = (value & 0x80) >> 7;
    left_volume = (value & 0x70) >> 4;
    right_vin = (value & 0x08) >> 3;
    right_volume = value & 0x07;
}

uint8_t APU::get_nr50() const {
    return (left_vin << 7) | (left_volume << 4) | (right_vin << 3) | right_volume;
}

void APU::set_nr51(uint8_t value) {
    c4_left = (value & 0x80) >> 7;
    c3_left = (value & 0x40) >> 6;
    c2_left = (value & 0x20) >> 5;
    c1_left = (value & 0x10) >> 4;
    c4_right = (value & 0x08) >> 3;
    c3_right = (value & 0x04) >> 2;
    c2_right = (value & 0x02) >> 1;
    c1_right = (value & 0x01);
}

uint8_t APU::get_nr51() const {
    return (c4_left << 7) | (c3_left << 6) | (c2_left << 5) | (c1_left << 4)
        | (c4_right << 3) | (c3_right << 2) | (c2_right << 1) | c1_right;
}

void APU::set_nr52(uint8_t value) {
    apu_on = (value & 0x80) >> 7;
}

uint8_t APU::get_nr52() const {
    return (apu_on << 7) | (channel4.is_enabled() << 3) | (channel3.is_enabled() << 2)
        | (channel2.is_enabled() << 1) | channel1.is_enabled();
}