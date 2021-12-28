#include "apu.h"

void APU::set_nr50(uint8_t value) {
    nr50 = value;
}

uint8_t APU::get_nr50() const {
    return nr50;
}