#include "register.h"

uint8_t Register8::get() {
    return value;
}

void Register8::set(uint8_t val) {
    value = val;
}

uint16_t Register16::get() {
    return (((uint16_t) high->get()) << 8) + low->get();
}

void Register16::set(uint16_t val) {
    high->set(val >> 8);
    low->set(val & 0xff);
}

void RegisterF::set(uint8_t val) {
    set(val & 0xf0);
}
