#pragma once

#include <cstdint>
#include <iostream>

class Register8 {
    public:
        uint8_t get() const;
        virtual void set(uint8_t val);
        friend std::ostream& operator<<(std::ostream& out, const Register8& reg);
    protected:
        uint8_t value = 0;
};

class Register16 {
    public:
        Register16(Register8* hi, Register8* lo);
        uint16_t get() const;
        uint8_t get_high() const;
        uint8_t get_low() const;
        void set(uint16_t val);
        void set(uint8_t high_val, uint8_t low_val);
        friend std::ostream& operator<<(std::ostream& out, const Register16& reg);
    private:
        Register8* high;
        Register8* low;
};

class RegisterF : public Register8 {
    public:
        void set(uint8_t val);
        bool get_zero() const;
        bool get_subtract() const;
        bool get_half_carry() const;
        bool get_carry() const;
        void set_zero(bool val);
        void set_subtract(bool val);
        void set_half_carry(bool val);
        void set_carry(bool val);
};

