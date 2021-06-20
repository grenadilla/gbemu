#pragma once

#include "register.h"
#include "memory.h"
#include "interrupts.h"

#include <cstdint>
#include <string>

class CPU {
    public:
        CPU(Interrupts* interrupts, Timer* timer, Memory* mem);
        void tick();

        // Debug functions
        void print_debug(uint8_t opcode);
        void print_line_debug(uint8_t opcode);
        void print_imm_debug();
        void print_mem_debug();
        uint8_t get_opcode_debug();
        uint16_t get_PC_debug();
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

        uint16_t PC = 0x0100;
        uint16_t SP = 0xFFFE;

        bool jump_taken = false;

        bool halted = false;
        bool halt_bug = false;

        // TODO make shared pointer?
        Interrupts* interrupts;
        Memory* mem;
        Timer* timer;

        typedef void (CPU::*MemFuncPtr)();
        struct Opcode {
            uint8_t opcode;
            bool extended;
            // Debug string with human readable formatting
            std::string debug;
            // Number of machine cycles opcode takes
            // For control opcodes this is if taken
            unsigned cycles;
            // For control opcodes this is if not taken, 0 otherwise
            unsigned not_taken_cycles;
            // Pointer to opcode function
            MemFuncPtr func;
        };

        friend std::ostream& operator<<(std::ostream& out, const Opcode& op);

        static Opcode opcode_table[256];
        static Opcode opcode_prefixed_table[256];
        //MemFuncPtr opcode_table[1] = {&CPU::set_a};
        // Calling a function in the table
        //(this->*(opcode_table[0]))();
       
        unsigned run_opcode();

        // --opcode Helper Functions--
        uint8_t retrieve_imm8();
        uint16_t retrieve_imm16();
        void push_stack(uint16_t val);
        uint16_t pop_stack();

        void halt();

        // --Loads--
        void load_reg(Register8& reg, const Register8& data);
        void load_reg(const Register16& ptr, const Register8& data);
        void load_reg_inc(const Register8& data);
        void load_reg_dec(const Register8& data);

        void load_mem(Register8& reg, const Register16& ptr);
        void load_mem_inc(Register8& reg);
        void load_mem_dec(Register8& reg);

        void load_imm(Register8& reg);
        void load_imm(Register16& reg);
        void load_imm();

        void load_reg_to_mem_imm(const Register8& data);
        void load_mem_imm_to_reg(Register8& reg);

        void load_reg_to_upper_mem_imm(const Register8& data);
        void load_upper_mem_imm_to_reg(Register8& reg);

        void load_reg_to_upper_mem_reg(Register8& upper_ptr, Register8& data);
        void load_upper_mem_reg_to_reg(Register8& reg, Register8& upper_ptr);

        void load_sp();

        // Increments and decrements
        void inc(Register8& reg);
        void inc(Register16& reg);
        void inc();
        void dec(Register8& reg);
        void dec(Register16& reg);
        void dec();

        // Arithmetic on accumulator register
        void add(Register8& dest, uint8_t val);
        void add(const Register8& reg);
        void add();
        void add_imm();

        void addc(Register8& dest, uint8_t val);
        void addc(const Register8& reg);
        void addc();
        void addc_imm();

        void sub(Register8& dest, uint8_t val);
        void sub(const Register8& reg);
        void sub();
        void sub_imm();

        void subc(Register8& dest, uint8_t val);
        void subc(const Register8& reg);
        void subc();
        void subc_imm();

        void add_HL(const Register16& reg);
        void add_HL(uint16_t val);

        void add_SP();

        // Logic on accumulator register
        void op_and(const Register8& reg);
        void op_and();
        void op_and_imm();
        void op_xor(const Register8& reg);
        void op_xor();
        void op_xor_imm();
        void op_or(const Register8& reg);
        void op_or();
        void op_or_imm();

        // Compare with accumulator register
        void cp(const Register8& reg);
        void cp();
        void cp_imm();

        // Stack opcodes
        void load_HL();
        void pop(Register16& reg);
        void push(Register16& reg);
        void load_SP();

        // Control opcodes
        void jump(uint16_t to);
        void call(bool condition = true);
        void ret(bool condition = true);
        void jr(bool condition = true);
        void jp(bool condition = true);
        void jp_mem();
        // TODO RETI opcode

        // Restart opcodes
        void rst(uint8_t val);

        // Misc
        void daa();
        void scf();
        void cpl();
        void ccf();

        // Bit manipulation
        uint8_t rlc(uint8_t val);
        uint8_t rl(uint8_t val);
        uint8_t rrc(uint8_t val);
        uint8_t rr(uint8_t val);

        void rlc_a();
        void rl_a();
        void rrc_a();
        void rr_a();

        void rlc(Register8& reg);
        void rl(Register8& reg);
        void rrc(Register8& reg);
        void rr(Register8& reg);

        void rlc();
        void rl();
        void rrc();
        void rr();

        void sla(Register8& reg);
        void sla();
        void sra(Register8& reg);
        void sra();
        void swap(Register8& reg);
        void swap();
        void srl(Register8& reg);
        void srl();

        // Bit test and set
        void test_bit(const Register8& reg, uint8_t bit_num);
        void test_bit(uint8_t bit_num);
        void res_bit(Register8& reg, uint8_t bit_num);
        void res_bit(uint8_t bit_num);
        void set_bit(Register8& reg, uint8_t bit_num);
        void set_bit(uint8_t bit_num);
        
        // --opcodes--
        // --NOP--
        void opcode_00(); void opcode_10(); void opcode_76(); void opcode_F3(); void opcode_FB();
        void opcode_illegal();

        // --Loads--
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

        // --Increment and decrement--
        void opcode_03(); void opcode_13(); void opcode_23(); void opcode_33();
        void opcode_04(); void opcode_14(); void opcode_24(); void opcode_34();
        void opcode_05(); void opcode_15(); void opcode_25(); void opcode_35();
        void opcode_0B(); void opcode_1B(); void opcode_2B(); void opcode_3B();
        void opcode_0C(); void opcode_1C(); void opcode_2C(); void opcode_3C();
        void opcode_0D(); void opcode_1D(); void opcode_2D(); void opcode_3D();

        // --Arithmetic--
        void opcode_80(); void opcode_81(); void opcode_82(); void opcode_83(); void opcode_84();
        void opcode_85(); void opcode_86(); void opcode_87(); void opcode_88(); void opcode_89();
        void opcode_8A(); void opcode_8B(); void opcode_8C(); void opcode_8D(); void opcode_8E();
        void opcode_8F(); void opcode_90(); void opcode_91(); void opcode_92(); void opcode_93();
        void opcode_94(); void opcode_95(); void opcode_96(); void opcode_97(); void opcode_98();
        void opcode_99(); void opcode_9A(); void opcode_9B(); void opcode_9C(); void opcode_9D();
        void opcode_9E(); void opcode_9F();
        void opcode_C6(); void opcode_D6(); void opcode_CE(); void opcode_DE();
        void opcode_09(); void opcode_19(); void opcode_29(); void opcode_39(); void opcode_E8();

        // --Logical--
        void opcode_A0(); void opcode_A1(); void opcode_A2(); void opcode_A3(); void opcode_A4();
        void opcode_A5(); void opcode_A6(); void opcode_A7(); void opcode_A8(); void opcode_A9();
        void opcode_AA(); void opcode_AB(); void opcode_AC(); void opcode_AD(); void opcode_AE();
        void opcode_AF(); void opcode_B0(); void opcode_B1(); void opcode_B2(); void opcode_B3();
        void opcode_B4(); void opcode_B5(); void opcode_B6(); void opcode_B7(); 

        void opcode_E6(); void opcode_F6(); void opcode_EE(); void opcode_FE();

        // --Compare--
        void opcode_B8(); void opcode_B9(); void opcode_BA(); void opcode_BB(); void opcode_BC(); 
        void opcode_BD(); void opcode_BE(); void opcode_BF();

        // --Stack--
        void opcode_C1(); void opcode_D1(); void opcode_E1(); void opcode_F1(); void opcode_F8();
        void opcode_C5(); void opcode_D5(); void opcode_E5(); void opcode_F5(); void opcode_F9();

        // --Control--
        void opcode_20(); void opcode_30(); void opcode_18(); void opcode_28(); void opcode_38();
        void opcode_C0(); void opcode_D0(); void opcode_C8(); void opcode_D8(); void opcode_C9();
        void opcode_D9();
        void opcode_C2(); void opcode_D2(); void opcode_C3(); void opcode_CA(); void opcode_DA();
        void opcode_E9();

        // --Restart--
        void opcode_C4(); void opcode_D4(); void opcode_CC(); void opcode_DC(); void opcode_CD();
        void opcode_C7(); void opcode_CF(); void opcode_D7(); void opcode_DF();
        void opcode_E7(); void opcode_EF(); void opcode_F7(); void opcode_FF();

        // --Misc--
        void opcode_27(); void opcode_37(); void opcode_2F(); void opcode_3F();

        // --Bit manipulation--
        void opcode_07(); void opcode_17(); void opcode_0F(); void opcode_1F();

        void opcode_CB00(); void opcode_CB01(); void opcode_CB02(); void opcode_CB03();
        void opcode_CB04(); void opcode_CB05(); void opcode_CB06(); void opcode_CB07();
        void opcode_CB08(); void opcode_CB09(); void opcode_CB0A(); void opcode_CB0B();
        void opcode_CB0C(); void opcode_CB0D(); void opcode_CB0E(); void opcode_CB0F();

        void opcode_CB10(); void opcode_CB11(); void opcode_CB12(); void opcode_CB13();
        void opcode_CB14(); void opcode_CB15(); void opcode_CB16(); void opcode_CB17();
        void opcode_CB18(); void opcode_CB19(); void opcode_CB1A(); void opcode_CB1B();
        void opcode_CB1C(); void opcode_CB1D(); void opcode_CB1E(); void opcode_CB1F();

        void opcode_CB20(); void opcode_CB21(); void opcode_CB22(); void opcode_CB23();
        void opcode_CB24(); void opcode_CB25(); void opcode_CB26(); void opcode_CB27();
        void opcode_CB28(); void opcode_CB29(); void opcode_CB2A(); void opcode_CB2B();
        void opcode_CB2C(); void opcode_CB2D(); void opcode_CB2E(); void opcode_CB2F();

        void opcode_CB30(); void opcode_CB31(); void opcode_CB32(); void opcode_CB33();
        void opcode_CB34(); void opcode_CB35(); void opcode_CB36(); void opcode_CB37();
        void opcode_CB38(); void opcode_CB39(); void opcode_CB3A(); void opcode_CB3B();
        void opcode_CB3C(); void opcode_CB3D(); void opcode_CB3E(); void opcode_CB3F();

        void opcode_CB40(); void opcode_CB41(); void opcode_CB42(); void opcode_CB43();
        void opcode_CB44(); void opcode_CB45(); void opcode_CB46(); void opcode_CB47();
        void opcode_CB48(); void opcode_CB49(); void opcode_CB4A(); void opcode_CB4B();
        void opcode_CB4C(); void opcode_CB4D(); void opcode_CB4E(); void opcode_CB4F();

        void opcode_CB50(); void opcode_CB51(); void opcode_CB52(); void opcode_CB53();
        void opcode_CB54(); void opcode_CB55(); void opcode_CB56(); void opcode_CB57();
        void opcode_CB58(); void opcode_CB59(); void opcode_CB5A(); void opcode_CB5B();
        void opcode_CB5C(); void opcode_CB5D(); void opcode_CB5E(); void opcode_CB5F();

        void opcode_CB60(); void opcode_CB61(); void opcode_CB62(); void opcode_CB63();
        void opcode_CB64(); void opcode_CB65(); void opcode_CB66(); void opcode_CB67();
        void opcode_CB68(); void opcode_CB69(); void opcode_CB6A(); void opcode_CB6B();
        void opcode_CB6C(); void opcode_CB6D(); void opcode_CB6E(); void opcode_CB6F();

        void opcode_CB70(); void opcode_CB71(); void opcode_CB72(); void opcode_CB73();
        void opcode_CB74(); void opcode_CB75(); void opcode_CB76(); void opcode_CB77();
        void opcode_CB78(); void opcode_CB79(); void opcode_CB7A(); void opcode_CB7B();
        void opcode_CB7C(); void opcode_CB7D(); void opcode_CB7E(); void opcode_CB7F();

        void opcode_CB80(); void opcode_CB81(); void opcode_CB82(); void opcode_CB83();
        void opcode_CB84(); void opcode_CB85(); void opcode_CB86(); void opcode_CB87();
        void opcode_CB88(); void opcode_CB89(); void opcode_CB8A(); void opcode_CB8B();
        void opcode_CB8C(); void opcode_CB8D(); void opcode_CB8E(); void opcode_CB8F();

        void opcode_CB90(); void opcode_CB91(); void opcode_CB92(); void opcode_CB93();
        void opcode_CB94(); void opcode_CB95(); void opcode_CB96(); void opcode_CB97();
        void opcode_CB98(); void opcode_CB99(); void opcode_CB9A(); void opcode_CB9B();
        void opcode_CB9C(); void opcode_CB9D(); void opcode_CB9E(); void opcode_CB9F();
        
        void opcode_CBA0(); void opcode_CBA1(); void opcode_CBA2(); void opcode_CBA3();
        void opcode_CBA4(); void opcode_CBA5(); void opcode_CBA6(); void opcode_CBA7();
        void opcode_CBA8(); void opcode_CBA9(); void opcode_CBAA(); void opcode_CBAB();
        void opcode_CBAC(); void opcode_CBAD(); void opcode_CBAE(); void opcode_CBAF();

        void opcode_CBB0(); void opcode_CBB1(); void opcode_CBB2(); void opcode_CBB3();
        void opcode_CBB4(); void opcode_CBB5(); void opcode_CBB6(); void opcode_CBB7();
        void opcode_CBB8(); void opcode_CBB9(); void opcode_CBBA(); void opcode_CBBB();
        void opcode_CBBC(); void opcode_CBBD(); void opcode_CBBE(); void opcode_CBBF();

        void opcode_CBC0(); void opcode_CBC1(); void opcode_CBC2(); void opcode_CBC3();
        void opcode_CBC4(); void opcode_CBC5(); void opcode_CBC6(); void opcode_CBC7();
        void opcode_CBC8(); void opcode_CBC9(); void opcode_CBCA(); void opcode_CBCB();
        void opcode_CBCC(); void opcode_CBCD(); void opcode_CBCE(); void opcode_CBCF();
        
        void opcode_CBD0(); void opcode_CBD1(); void opcode_CBD2(); void opcode_CBD3();
        void opcode_CBD4(); void opcode_CBD5(); void opcode_CBD6(); void opcode_CBD7();
        void opcode_CBD8(); void opcode_CBD9(); void opcode_CBDA(); void opcode_CBDB();
        void opcode_CBDC(); void opcode_CBDD(); void opcode_CBDE(); void opcode_CBDF();
        
        void opcode_CBE0(); void opcode_CBE1(); void opcode_CBE2(); void opcode_CBE3();
        void opcode_CBE4(); void opcode_CBE5(); void opcode_CBE6(); void opcode_CBE7();
        void opcode_CBE8(); void opcode_CBE9(); void opcode_CBEA(); void opcode_CBEB();
        void opcode_CBEC(); void opcode_CBED(); void opcode_CBEE(); void opcode_CBEF();
        
        void opcode_CBF0(); void opcode_CBF1(); void opcode_CBF2(); void opcode_CBF3();
        void opcode_CBF4(); void opcode_CBF5(); void opcode_CBF6(); void opcode_CBF7();
        void opcode_CBF8(); void opcode_CBF9(); void opcode_CBFA(); void opcode_CBFB();
        void opcode_CBFC(); void opcode_CBFD(); void opcode_CBFE(); void opcode_CBFF();
};
