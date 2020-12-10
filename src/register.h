#pragma once

#include <cstdint>

class Register8 {
    public:
        uint8_t get();
        void set(uint8_t val);
    protected:
        uint8_t value = 0;
};

class Register16 {
    public:
        Register16(Register8* hi, Register8* lo);
        uint16_t get();
        void set(uint16_t val);
    private:
        Register8* high;
        Register8* low;
};

class RegisterF : public Register8 {
    public:
        void set(uint8_t val);
        uint8_t get_zero();
        uint8_t get_subtract();
        uint8_t get_half_carry();
        uint8_t get_carry();
};

