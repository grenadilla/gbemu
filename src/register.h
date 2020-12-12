#pragma once

#include <cstdint>

class Register8 {
    public:
        uint8_t get() const;
        void set(uint8_t val);
    protected:
        uint8_t value = 0;
};

class Register16 {
    public:
        Register16(Register8* hi, Register8* lo);
        uint16_t get() const;
        void set(uint16_t val);
    private:
        Register8* high;
        Register8* low;
};

class RegisterF : public Register8 {
    public:
        void set(uint8_t val);
        uint8_t get_zero() const;
        uint8_t get_subtract() const;
        uint8_t get_half_carry() const;
        uint8_t get_carry() const;
};

