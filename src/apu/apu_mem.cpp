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

void APU::set_nr50(uint8_t value) {
    nr50 = value;
}

uint8_t APU::get_nr50() const {
    return nr50;
}