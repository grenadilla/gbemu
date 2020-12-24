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
        uint16_t retrieve_imm16();

        // --Loads--
        void load_reg_to_mem(const Register16& ptr, const Register8& data);
        void load_reg_to_mem_inc(const Register8& data);
        void load_reg_to_mem_dec(const Register8& data);

        void load_mem_to_reg(Register8& reg, const Register16& ptr);
        void load_mem_to_reg_inc(Register8& reg);
        void load_mem_to_reg_dec(Register8& reg);

        void load_imm_to_reg(Register8& reg);
        void load_imm_to_mem();

        void load_reg_to_reg(Register8& reg, const Register8& data);

        void load_reg_to_mem_imm(const Register8& data);
        void load_mem_imm_to_reg(Register8& reg);

        void load_reg_to_upper_mem_imm(const Register8& data);
        void load_upper_mem_imm_to_reg(Register8& reg);

        void load_reg_to_upper_mem_reg(Register8& upper_ptr, Register8& data);
        void load_upper_mem_reg_to_reg(Register8& reg, Register8& upper_ptr);

        void load_imm_to_reg16(Register16& reg);
        void load_sp_to_mem();

        // Increments and decrements
        void inc_reg8(Register8& reg);
        void inc_reg16(Register16& reg);
        void inc_mem();
        void dec_reg8(Register8& reg);
        void dec_reg16(Register16& reg);
        void dec_mem();

        // Arithmetic on accumulator register
        void add(Register8& dest, uint8_t val);
        void add_reg(const Register8& reg);
        void add_mem();
        void add_imm();

        void addc(Register8& dest, uint8_t val);
        void addc_reg(const Register8& reg);
        void addc_mem();
        void addc_imm();

        void sub(Register8& dest, uint8_t val);
        void sub_reg(const Register8& reg);
        void sub_mem();
        void sub_imm();

        void subc(Register8& dest, uint8_t val);
        void subc_reg(const Register8& reg);
        void subc_mem();
        void subc_imm();

        void add_HL(const Register16& reg);
        void add_HL(uint16_t val);

        void add_SP();

        // Logic on accumulator register
        void and_reg(const Register8& reg);
        void and_mem();
        void xor_reg(const Register8& reg);
        void xor_mem();
        void or_reg(const Register8& reg);
        void or_mem();
        
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

        void opcode_01(); void opcode_11(); void opcode_21(); void opcode_31(); void opcode_08();

        // --Increment and decrement opcodes--
        void opcode_03(); void opcode_13(); void opcode_23(); void opcode_33();
        void opcode_04(); void opcode_14(); void opcode_24(); void opcode_34();
        void opcode_05(); void opcode_15(); void opcode_25(); void opcode_35();
        void opcode_0B(); void opcode_1B(); void opcode_2B(); void opcode_3B();
        void opcode_0C(); void opcode_1C(); void opcode_2C(); void opcode_3C();
        void opcode_0D(); void opcode_1D(); void opcode_2D(); void opcode_3D();

        // --Arithmetic opcodes--
        void opcode_80(); void opcode_81(); void opcode_82(); void opcode_83(); void opcode_84();
        void opcode_85(); void opcode_86(); void opcode_87(); void opcode_88(); void opcode_89();
        void opcode_8A(); void opcode_8B(); void opcode_8C(); void opcode_8D(); void opcode_8E();
        void opcode_8F(); void opcode_90(); void opcode_91(); void opcode_92(); void opcode_93();
        void opcode_94(); void opcode_95(); void opcode_96(); void opcode_97(); void opcode_98();
        void opcode_99(); void opcode_9A(); void opcode_9B(); void opcode_9C(); void opcode_9D();
        void opcode_9E(); void opcode_9F();
        void opcode_C6(); void opcode_D6(); void opcode_CE(); void opcode_DE();
        void opcode_09(); void opcode_19(); void opcode_29(); void opcode_39(); void opcode_E8();

        // --Logical opcodes--
        void opcode_A0(); void opcode_A1(); void opcode_A2(); void opcode_A3(); void opcode_A4();
        void opcode_A5(); void opcode_A6(); void opcode_A7(); void opcode_A8(); void opcode_A9();
        void opcode_AA(); void opcode_AB(); void opcode_AC(); void opcode_AD(); void opcode_AE();
        void opcode_AF(); void opcode_B0(); void opcode_B1(); void opcode_B2(); void opcode_B3();
        void opcode_B4(); void opcode_B5(); void opcode_B6(); void opcode_B7(); 

        // --Compare opcodes--
        void opcode_B8(); void opcode_B9(); void opcode_BA(); void opcode_BB(); void opcode_BC(); 
        void opcode_BD(); void opcode_BE(); void opcode_BF();
};
