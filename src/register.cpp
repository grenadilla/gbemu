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
    return ((static_cast<uint16_t>(high->get())) << 8) + low->get();
}

uint8_t Register16::get_high() const {
    return high->get();
}

uint8_t Register16::get_low() const {
    return low->get();
}

void Register16::set(uint16_t val) {
    high->set(val >> 8);
    low->set(val & 0xff);
}

void Register16::set(uint8_t high_val, uint8_t low_val) {
    high->set(high_val);
    low->set(low_val);
}

void RegisterF::set(uint8_t val) {
    value = val & 0xf0;
}

bool RegisterF::get_zero() const {
    return value >> 7;
}

bool RegisterF::get_subtract() const {
    return (value >> 6) & 0x1;
}

bool RegisterF::get_half_carry() const {
    return (value >> 5) & 0x1;
}

bool RegisterF::get_carry() const {
    return (value >> 4) & 0x1;
}

void RegisterF::set_zero(bool val) {
    value &= 0x7F;
    value |= (val << 7);
}

void RegisterF::set_subtract(bool val) {
    value &= 0xBF;
    value |= (val << 6);
}

void RegisterF::set_half_carry(bool val) {
    value &= 0xDF;
    value |= (val << 5);
}

void RegisterF::set_carry(bool val) {
    value &= 0xEF;
    value |= (val << 4);
}
