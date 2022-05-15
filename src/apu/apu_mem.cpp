#include "apu.h"

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

void APU::set_nr50(uint8_t value) {
    nr50 = value;
}

uint8_t APU::get_nr50() const {
    return nr50;
}