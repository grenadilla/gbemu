#include "register.h"

uint8_t Register8::get() const {
    return value;
}

void Register8::set(uint8_t val) {
    value = val;
}

Register16::Register16(Register8* hi, Register8* lo) {
    high = hi;
    low = lo;
}

uint16_t Register16::get() const {
    return (((uint16_t) high->get()) << 8) + low->get();
}

void Register16::set(uint16_t val) {
    high->set(val >> 8);
    low->set(val & 0xff);
}

void RegisterF::set(uint8_t val) {
    set(val & 0xf0);
}

uint8_t RegisterF::get_zero() const {
    return value >> 7;
}

uint8_t RegisterF::get_subtract() const {
    return (value >> 6) & 0x1;
}

uint8_t RegisterF::get_half_carry() const {
    return (value >> 5) & 0x1;
}

uint8_t RegisterF::get_carry() const {
    return (value >> 4) & 0x1;
}
