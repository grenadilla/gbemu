#pragma once

#include <cstdint>
#include <string>
#include "register.h"

class CPU {
    public:
        CPU();
    private:
        Register8 A;
        Register8 B;
        Register8 C;
        Register8 D;
        Register8 E;
        Register8 H;
        Register8 L;
        RegisterF F;

        Register16 AF;
        Register16 BC;
        Register16 DE;
        Register16 HL;

        uint16_t PC;
        uint16_t SP;

        typedef void (CPU::*MemFuncPtr)();
        //MemFuncPtr opcode_table[1] = {&CPU::set_a};
        // Calling a function in the table
        //(this->*(opcode_table[0]))();
};
