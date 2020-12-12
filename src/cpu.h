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

        // TODO add memory mappings and change from simple array
        uint8_t RAM[65536] = {0};

        typedef void (CPU::*MemFuncPtr)();
        struct Opcode {
            // Opcode including prefix 
            // 0x00xx if no prefix, 0xCBxx if has prefix
            uint16_t opcode;
            // Debug string with human readable formatting
            std::string debug;
            // Number of bytes opcode takes including prefix and parameters
            unsigned bytes;
            // Number of machine cycles opcode takes
            // For control opcodes this is if taken
            unsigned cycles;
            // For control opcodes this is if not taken, 0 otherwise
            unsigned not_taken_cycles;
            // Pointer to opcode function
            MemFuncPtr func;
        };

        static Opcode opcode_table[256];
        static Opcode opcode_prefixed_table[256];
        //MemFuncPtr opcode_table[1] = {&CPU::set_a};
        // Calling a function in the table
        //(this->*(opcode_table[0]))();
        
        // --opcode Helper Functions--

        // --Loads--
        void load_reg_to_mem(const Register16& ptr, const Register8& data);
        void load_reg_to_mem_inc(Register16& ptr, const Register8& data);
        void load_reg_to_mem_dec(Register16& ptr, const Register8& data);

        void load_mem_to_reg(Register8& reg, const Register16& ptr);
        void load_mem_to_reg_inc(Register8& reg, Register16& ptr);
        void load_mem_to_reg_dec(Register8& reg, Register16& ptr);

        void load_imm_to_reg(Register8& reg, uint8_t imm);
        void load_imm_to_mem(const Register16& ptr, uint8_t imm);

        void load_reg_to_reg(Register8& reg, const Register8& data);

        // TODO Load RAM, port register, or mode register

        // --opcodes--
        // --NOP--
        void opcode_00();

        // --Load opcodes--
        void opcode_02(); void opcode_06(); void opcode_0A(); void opcode_0E(); void opcode_12();
        void opcode_16(); void opcode_1A(); void opcode_1E(); void opcode_22(); void opcode_26();
        void opcode_2A(); void opcode_2E(); void opcode_32(); void opcode_36(); void opcode_3A();
        void opcode_3E(); void opcode_40(); void opcode_41(); void opcode_42(); void opcode_43();
        void opcode_44(); void opcode_45(); void opcode_46(); void opcode_47(); void opcode_48();
        void opcode_49(); void opcode_4A(); void opcode_4B(); void opcode_4C(); void opcode_4D();
        void opcode_4E(); void opcode_4F(); void opcode_50(); void opcode_51(); void opcode_52();
        void opcode_53(); void opcode_54(); void opcode_55(); void opcode_56(); void opcode_57();
        void opcode_58(); void opcode_59(); void opcode_5A(); void opcode_5B(); void opcode_5C();
        void opcode_5D(); void opcode_5E(); void opcode_5F(); void opcode_60(); void opcode_61();
        void opcode_62(); void opcode_63(); void opcode_64(); void opcode_65(); void opcode_66();
        void opcode_67(); void opcode_68(); void opcode_69(); void opcode_6A(); void opcode_6B();
        void opcode_6C(); void opcode_6D(); void opcode_6E(); void opcode_6F(); void opcode_70();
        void opcode_71(); void opcode_72(); void opcode_73(); void opcode_74(); void opcode_75();
        // Note we skip opcode_76() as that is the HALT instruction
        void opcode_77(); void opcode_78(); void opcode_79(); void opcode_7A(); void opcode_7B();
        void opcode_7C(); void opcode_7D(); void opcode_7E(); void opcode_7F(); void opcode_E0();
        void opcode_E2(); void opcode_EA(); void opcode_F0(); void opcode_F2(); void opcode_FA();
};
