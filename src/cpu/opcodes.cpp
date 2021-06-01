#include "cpu.h"

void CPU::opcode_00() {}
// TODO STOP Ignored
void CPU::opcode_10() {}
// TODO HALT
void CPU::opcode_76() { halt(); }
// TODO DI
void CPU::opcode_F3() { interrupts->disable_interrupts(); }
// TODO EI
void CPU::opcode_FB() { interrupts->enable_interrupts(); }

// Loads
void CPU::opcode_02() { load_reg(BC, A); }
void CPU::opcode_06() { load_imm(B); }
void CPU::opcode_0A() { load_mem(A, BC); }
void CPU::opcode_0E() { load_imm(C); }
void CPU::opcode_12() { load_reg(DE, A); }
void CPU::opcode_16() { load_imm(D); }
void CPU::opcode_1A() { load_mem(A, DE); }
void CPU::opcode_1E() { load_imm(E); }
void CPU::opcode_22() { load_reg_inc(A); }
void CPU::opcode_26() { load_imm(H); }
void CPU::opcode_2A() { load_mem_inc(A); }
void CPU::opcode_2E() { load_imm(L); }
void CPU::opcode_32() { load_reg_dec(A); }
void CPU::opcode_36() { load_imm(); }
void CPU::opcode_3A() { load_mem_dec(A); }
void CPU::opcode_3E() { load_imm(A); }

void CPU::opcode_40() { load_reg(B, B); }
void CPU::opcode_41() { load_reg(B, C); }
void CPU::opcode_42() { load_reg(B, D); }
void CPU::opcode_43() { load_reg(B, E); }
void CPU::opcode_44() { load_reg(B, H); }
void CPU::opcode_45() { load_reg(B, L); }
void CPU::opcode_46() { load_mem(B, HL); }
void CPU::opcode_47() { load_reg(B, A); }

void CPU::opcode_48() { load_reg(C, B); }
void CPU::opcode_49() { load_reg(C, C); }
void CPU::opcode_4A() { load_reg(C, D); }
void CPU::opcode_4B() { load_reg(C, E); }
void CPU::opcode_4C() { load_reg(C, H); }
void CPU::opcode_4D() { load_reg(C, L); }
void CPU::opcode_4E() { load_mem(C, HL); }
void CPU::opcode_4F() { load_reg(C, A); }

void CPU::opcode_50() { load_reg(D, B); }
void CPU::opcode_51() { load_reg(D, C); }
void CPU::opcode_52() { load_reg(D, D); }
void CPU::opcode_53() { load_reg(D, E); }
void CPU::opcode_54() { load_reg(D, H); }
void CPU::opcode_55() { load_reg(D, L); }
void CPU::opcode_56() { load_mem(D, HL); }
void CPU::opcode_57() { load_reg(D, A); }

void CPU::opcode_58() { load_reg(E, B); }
void CPU::opcode_59() { load_reg(E, C); }
void CPU::opcode_5A() { load_reg(E, D); }
void CPU::opcode_5B() { load_reg(E, E); }
void CPU::opcode_5C() { load_reg(E, H); }
void CPU::opcode_5D() { load_reg(E, L); }
void CPU::opcode_5E() { load_mem(E, HL); }
void CPU::opcode_5F() { load_reg(E, A); }

void CPU::opcode_60() { load_reg(H, B); }
void CPU::opcode_61() { load_reg(H, C); }
void CPU::opcode_62() { load_reg(H, D); }
void CPU::opcode_63() { load_reg(H, E); }
void CPU::opcode_64() { load_reg(H, H); }
void CPU::opcode_65() { load_reg(H, L); }
void CPU::opcode_66() { load_mem(H, HL); }
void CPU::opcode_67() { load_reg(H, A); }

void CPU::opcode_68() { load_reg(L, B); }
void CPU::opcode_69() { load_reg(L, C); }
void CPU::opcode_6A() { load_reg(L, D); }
void CPU::opcode_6B() { load_reg(L, E); }
void CPU::opcode_6C() { load_reg(L, H); }
void CPU::opcode_6D() { load_reg(L, L); }
void CPU::opcode_6E() { load_mem(L, HL); }
void CPU::opcode_6F() { load_reg(L, A); }

void CPU::opcode_70() { load_reg(HL, B); }
void CPU::opcode_71() { load_reg(HL, C); }
void CPU::opcode_72() { load_reg(HL, D); }
void CPU::opcode_73() { load_reg(HL, E); }
void CPU::opcode_74() { load_reg(HL, H); }
void CPU::opcode_75() { load_reg(HL, L); }
// Skip opcode_76 which is HALT
void CPU::opcode_77() { load_reg(HL, A); }

void CPU::opcode_78() { load_reg(A, B); }
void CPU::opcode_79() { load_reg(A, C); }
void CPU::opcode_7A() { load_reg(A, D); }
void CPU::opcode_7B() { load_reg(A, E); }
void CPU::opcode_7C() { load_reg(A, H); }
void CPU::opcode_7D() { load_reg(A, L); }
void CPU::opcode_7E() { load_mem(A, HL); }
void CPU::opcode_7F() { load_reg(A, A); }

void CPU::opcode_E0() { load_reg_to_upper_mem_imm(A); }
void CPU::opcode_E2() { load_reg_to_upper_mem_reg(C, A); }
void CPU::opcode_EA() { load_reg_to_mem_imm(A); }
void CPU::opcode_F0() { load_upper_mem_imm_to_reg(A); }
void CPU::opcode_F2() { load_upper_mem_reg_to_reg(A, C); }
void CPU::opcode_FA() { load_mem_imm_to_reg(A); }

void CPU::opcode_01() { load_imm(BC); }
void CPU::opcode_11() { load_imm(DE); }
void CPU::opcode_21() { load_imm(HL); }
void CPU::opcode_31() { SP = retrieve_imm16(); }
void CPU::opcode_08() { load_sp(); }

// Increments and decrements
void CPU::opcode_03() { inc(BC); }
void CPU::opcode_13() { inc(DE); }
void CPU::opcode_23() { inc(HL); }
void CPU::opcode_33() { SP++; }
void CPU::opcode_04() { inc(B); }
void CPU::opcode_14() { inc(D); }
void CPU::opcode_24() { inc(H); }
void CPU::opcode_34() { inc(); }
void CPU::opcode_05() { dec(B); }
void CPU::opcode_15() { dec(D); }
void CPU::opcode_25() { dec(H); }
void CPU::opcode_35() { dec(); }
void CPU::opcode_0B() { dec(BC); }
void CPU::opcode_1B() { dec(DE); }
void CPU::opcode_2B() { dec(HL); }
void CPU::opcode_3B() { SP--; }
void CPU::opcode_0C() { inc(C); }
void CPU::opcode_1C() { inc(E); }
void CPU::opcode_2C() { inc(L); }
void CPU::opcode_3C() { inc(A); }
void CPU::opcode_0D() { dec(C); }
void CPU::opcode_1D() { dec(E); }
void CPU::opcode_2D() { dec(L); }
void CPU::opcode_3D() { dec(A); }

// Arithmetic
void CPU::opcode_80() { add(B); }
void CPU::opcode_81() { add(C); }
void CPU::opcode_82() { add(D); }
void CPU::opcode_83() { add(E); }
void CPU::opcode_84() { add(H); }
void CPU::opcode_85() { add(L); }
void CPU::opcode_86() { add(); }
void CPU::opcode_87() { add(A); }
void CPU::opcode_88() { addc(B); }
void CPU::opcode_89() { addc(C); }
void CPU::opcode_8A() { addc(D); }
void CPU::opcode_8B() { addc(E); }
void CPU::opcode_8C() { addc(H); }
void CPU::opcode_8D() { addc(L); }
void CPU::opcode_8E() { addc(); }
void CPU::opcode_8F() { addc(A); }

void CPU::opcode_90() { sub(B); }
void CPU::opcode_91() { sub(C); }
void CPU::opcode_92() { sub(D); }
void CPU::opcode_93() { sub(E); }
void CPU::opcode_94() { sub(H); }
void CPU::opcode_95() { sub(L); }
void CPU::opcode_96() { sub(); }
void CPU::opcode_97() { sub(A); }
void CPU::opcode_98() { subc(B); }
void CPU::opcode_99() { subc(C); }
void CPU::opcode_9A() { subc(D); }
void CPU::opcode_9B() { subc(E); }
void CPU::opcode_9C() { subc(H); }
void CPU::opcode_9D() { subc(L); }
void CPU::opcode_9E() { subc(); }
void CPU::opcode_9F() { subc(A); }

void CPU::opcode_C6() { add_imm(); }
void CPU::opcode_D6() { sub_imm(); }
void CPU::opcode_CE() { addc_imm(); }
void CPU::opcode_DE() { subc_imm(); }

void CPU::opcode_09() { add_HL(BC); }
void CPU::opcode_19() { add_HL(DE); }
void CPU::opcode_29() { add_HL(HL); }
void CPU::opcode_39() { add_HL(SP); }
void CPU::opcode_E8() { add_SP(); }

// Logic
void CPU::opcode_A0() { op_and(B); }
void CPU::opcode_A1() { op_and(C); }
void CPU::opcode_A2() { op_and(D); }
void CPU::opcode_A3() { op_and(E); }
void CPU::opcode_A4() { op_and(H); }
void CPU::opcode_A5() { op_and(L); }
void CPU::opcode_A6() { op_and(); }
void CPU::opcode_A7() { op_and(A); }

void CPU::opcode_A8() { op_xor(B); }
void CPU::opcode_A9() { op_xor(C); }
void CPU::opcode_AA() { op_xor(D); }
void CPU::opcode_AB() { op_xor(E); }
void CPU::opcode_AC() { op_xor(H); }
void CPU::opcode_AD() { op_xor(L); }
void CPU::opcode_AE() { op_xor(); }
void CPU::opcode_AF() { op_xor(A); }

void CPU::opcode_B0() { op_or(B); }
void CPU::opcode_B1() { op_or(C); }
void CPU::opcode_B2() { op_or(D); }
void CPU::opcode_B3() { op_or(E); }
void CPU::opcode_B4() { op_or(H); }
void CPU::opcode_B5() { op_or(L); }
void CPU::opcode_B6() { op_or(); }
void CPU::opcode_B7() { op_or(A); }

// Immediate logic
void CPU::opcode_E6() { op_and_imm(); }
void CPU::opcode_F6() { op_or_imm(); }
void CPU::opcode_EE() { op_xor_imm(); }
void CPU::opcode_FE() { cp_imm(); }

// Compare
void CPU::opcode_B8() { cp(B); }
void CPU::opcode_B9() { cp(C); }
void CPU::opcode_BA() { cp(D); }
void CPU::opcode_BB() { cp(E); }
void CPU::opcode_BC() { cp(H); }
void CPU::opcode_BD() { cp(L); }
void CPU::opcode_BE() { cp(); }
void CPU::opcode_BF() { cp(A); }

// Stack
void CPU::opcode_C1() { pop(BC); }
void CPU::opcode_D1() { pop(DE); }
void CPU::opcode_E1() { pop(HL); }
void CPU::opcode_F1() { pop(AF); }
void CPU::opcode_C5() { push(BC); }
void CPU::opcode_D5() { push(DE); }
void CPU::opcode_E5() { push(HL); }
void CPU::opcode_F5() { push(AF); }
void CPU::opcode_F8() { load_HL(); }
void CPU::opcode_F9() { load_SP(); }

// Control
void CPU::opcode_20() { jr(!F.get_zero()); }
void CPU::opcode_30() { jr(!F.get_carry()); }
void CPU::opcode_18() { jr(); }
void CPU::opcode_28() { jr(F.get_zero()); }
void CPU::opcode_38() { jr(F.get_carry()); }

void CPU::opcode_C0() { ret(!F.get_zero()); }
void CPU::opcode_D0() { ret(!F.get_carry()); }
void CPU::opcode_C8() { ret(F.get_zero()); }
void CPU::opcode_D8() { ret(F.get_carry()); }
void CPU::opcode_C9() { ret(); }
// TODO implement
void CPU::opcode_D9() { interrupts->enable_interrupts(); ret(); }

void CPU::opcode_C2() { jp(!F.get_zero()); }
void CPU::opcode_D2() { jp(!F.get_carry()); }
void CPU::opcode_C3() { jp(); }
void CPU::opcode_CA() { jp(F.get_zero()); }
void CPU::opcode_DA() { jp(F.get_carry()); }
void CPU::opcode_E9() { jp_mem(); }

void CPU::opcode_C4() { call(!F.get_zero()); }
void CPU::opcode_D4() { call(!F.get_carry()); }
void CPU::opcode_CC() { call(F.get_zero()); }
void CPU::opcode_DC() { call(F.get_carry()); }
void CPU::opcode_CD() { call(); }

void CPU::opcode_C7() { rst(0); }
void CPU::opcode_CF() { rst(1); }
void CPU::opcode_D7() { rst(2); }
void CPU::opcode_DF() { rst(3); }
void CPU::opcode_E7() { rst(4); }
void CPU::opcode_EF() { rst(5); }
void CPU::opcode_F7() { rst(6); }
void CPU::opcode_FF() { rst(7); }

// Misc
void CPU::opcode_27() { daa(); }
void CPU::opcode_37() { scf(); }
void CPU::opcode_2F() { cpl(); }
void CPU::opcode_3F() { ccf(); }

// Bit manipulation
void CPU::opcode_07() { rlc_a(); }
void CPU::opcode_17() { rl_a(); }
void CPU::opcode_0F() { rrc_a(); }
void CPU::opcode_1F() { rr_a(); }

void CPU::opcode_CB00() { rlc(B); }
void CPU::opcode_CB01() { rlc(C); }
void CPU::opcode_CB02() { rlc(D); }
void CPU::opcode_CB03() { rlc(E); }
void CPU::opcode_CB04() { rlc(H); }
void CPU::opcode_CB05() { rlc(L); }
void CPU::opcode_CB06() { rlc(); }
void CPU::opcode_CB07() { rlc(A); }

void CPU::opcode_CB08() { rrc(B); }
void CPU::opcode_CB09() { rrc(C); }
void CPU::opcode_CB0A() { rrc(D); }
void CPU::opcode_CB0B() { rrc(E); }
void CPU::opcode_CB0C() { rrc(H); }
void CPU::opcode_CB0D() { rrc(L); }
void CPU::opcode_CB0E() { rrc(); }
void CPU::opcode_CB0F() { rrc(A); }

void CPU::opcode_CB10() { rl(B); }
void CPU::opcode_CB11() { rl(C); }
void CPU::opcode_CB12() { rl(D); }
void CPU::opcode_CB13() { rl(E); }
void CPU::opcode_CB14() { rl(H); }
void CPU::opcode_CB15() { rl(L); }
void CPU::opcode_CB16() { rl(); }
void CPU::opcode_CB17() { rl(A); }

void CPU::opcode_CB18() { rr(B); }
void CPU::opcode_CB19() { rr(C); }
void CPU::opcode_CB1A() { rr(D); }
void CPU::opcode_CB1B() { rr(E); }
void CPU::opcode_CB1C() { rr(H); }
void CPU::opcode_CB1D() { rr(L); }
void CPU::opcode_CB1E() { rr(); }
void CPU::opcode_CB1F() { rr(A); }

void CPU::opcode_CB20() { sla(B); }
void CPU::opcode_CB21() { sla(C); }
void CPU::opcode_CB22() { sla(D); }
void CPU::opcode_CB23() { sla(E); }
void CPU::opcode_CB24() { sla(H); }
void CPU::opcode_CB25() { sla(L); }
void CPU::opcode_CB26() { sla(); }
void CPU::opcode_CB27() { sla(A); }

void CPU::opcode_CB28() { sra(B); }
void CPU::opcode_CB29() { sra(C); }
void CPU::opcode_CB2A() { sra(D); }
void CPU::opcode_CB2B() { sra(E); }
void CPU::opcode_CB2C() { sra(H); }
void CPU::opcode_CB2D() { sra(L); }
void CPU::opcode_CB2E() { sra(); }
void CPU::opcode_CB2F() { sra(A); }

void CPU::opcode_CB30() { swap(B); }
void CPU::opcode_CB31() { swap(C); }
void CPU::opcode_CB32() { swap(D); }
void CPU::opcode_CB33() { swap(E); }
void CPU::opcode_CB34() { swap(H); }
void CPU::opcode_CB35() { swap(L); }
void CPU::opcode_CB36() { swap(); }
void CPU::opcode_CB37() { swap(A); }

void CPU::opcode_CB38() { srl(B); }
void CPU::opcode_CB39() { srl(C); }
void CPU::opcode_CB3A() { srl(D); }
void CPU::opcode_CB3B() { srl(E); }
void CPU::opcode_CB3C() { srl(H); }
void CPU::opcode_CB3D() { srl(L); }
void CPU::opcode_CB3E() { srl(); }
void CPU::opcode_CB3F() { srl(A); }

void CPU::opcode_CB40() { test_bit(B, 0); }
void CPU::opcode_CB41() { test_bit(C, 0); }
void CPU::opcode_CB42() { test_bit(D, 0); }
void CPU::opcode_CB43() { test_bit(E, 0); }
void CPU::opcode_CB44() { test_bit(H, 0); }
void CPU::opcode_CB45() { test_bit(L, 0); }
void CPU::opcode_CB46() { test_bit(0); }
void CPU::opcode_CB47() { test_bit(A, 0); }

void CPU::opcode_CB48() { test_bit(B, 1); }
void CPU::opcode_CB49() { test_bit(C, 1); }
void CPU::opcode_CB4A() { test_bit(D, 1); }
void CPU::opcode_CB4B() { test_bit(E, 1); }
void CPU::opcode_CB4C() { test_bit(H, 1); }
void CPU::opcode_CB4D() { test_bit(L, 1); }
void CPU::opcode_CB4E() { test_bit(1); }
void CPU::opcode_CB4F() { test_bit(A, 1); }

void CPU::opcode_CB50() { test_bit(B, 2); }
void CPU::opcode_CB51() { test_bit(C, 2); }
void CPU::opcode_CB52() { test_bit(D, 2); }
void CPU::opcode_CB53() { test_bit(E, 2); }
void CPU::opcode_CB54() { test_bit(H, 2); }
void CPU::opcode_CB55() { test_bit(L, 2); }
void CPU::opcode_CB56() { test_bit(2); }
void CPU::opcode_CB57() { test_bit(A, 2); }

void CPU::opcode_CB58() { test_bit(B, 3); }
void CPU::opcode_CB59() { test_bit(C, 3); }
void CPU::opcode_CB5A() { test_bit(D, 3); }
void CPU::opcode_CB5B() { test_bit(E, 3); }
void CPU::opcode_CB5C() { test_bit(H, 3); }
void CPU::opcode_CB5D() { test_bit(L, 3); }
void CPU::opcode_CB5E() { test_bit(3); }
void CPU::opcode_CB5F() { test_bit(A, 3); }

void CPU::opcode_CB60() { test_bit(B, 4); }
void CPU::opcode_CB61() { test_bit(C, 4); }
void CPU::opcode_CB62() { test_bit(D, 4); }
void CPU::opcode_CB63() { test_bit(E, 4); }
void CPU::opcode_CB64() { test_bit(H, 4); }
void CPU::opcode_CB65() { test_bit(L, 4); }
void CPU::opcode_CB66() { test_bit(4); }
void CPU::opcode_CB67() { test_bit(A, 4); }

void CPU::opcode_CB68() { test_bit(B, 5); }
void CPU::opcode_CB69() { test_bit(C, 5); }
void CPU::opcode_CB6A() { test_bit(D, 5); }
void CPU::opcode_CB6B() { test_bit(E, 5); }
void CPU::opcode_CB6C() { test_bit(H, 5); }
void CPU::opcode_CB6D() { test_bit(L, 5); }
void CPU::opcode_CB6E() { test_bit(5); }
void CPU::opcode_CB6F() { test_bit(A, 5); }

void CPU::opcode_CB70() { test_bit(B, 6); }
void CPU::opcode_CB71() { test_bit(C, 6); }
void CPU::opcode_CB72() { test_bit(D, 6); }
void CPU::opcode_CB73() { test_bit(E, 6); }
void CPU::opcode_CB74() { test_bit(H, 6); }
void CPU::opcode_CB75() { test_bit(L, 6); }
void CPU::opcode_CB76() { test_bit(6); }
void CPU::opcode_CB77() { test_bit(A, 6); }

void CPU::opcode_CB78() { test_bit(B, 7); }
void CPU::opcode_CB79() { test_bit(C, 7); }
void CPU::opcode_CB7A() { test_bit(D, 7); }
void CPU::opcode_CB7B() { test_bit(E, 7); }
void CPU::opcode_CB7C() { test_bit(H, 7); }
void CPU::opcode_CB7D() { test_bit(L, 7); }
void CPU::opcode_CB7E() { test_bit(7); }
void CPU::opcode_CB7F() { test_bit(A, 7); }

void CPU::opcode_CB80() { res_bit(B, 0); }
void CPU::opcode_CB81() { res_bit(C, 0); }
void CPU::opcode_CB82() { res_bit(D, 0); }
void CPU::opcode_CB83() { res_bit(E, 0); }
void CPU::opcode_CB84() { res_bit(H, 0); }
void CPU::opcode_CB85() { res_bit(L, 0); }
void CPU::opcode_CB86() { res_bit(0); }
void CPU::opcode_CB87() { res_bit(A, 0); }

void CPU::opcode_CB88() { res_bit(B, 1); }
void CPU::opcode_CB89() { res_bit(C, 1); }
void CPU::opcode_CB8A() { res_bit(D, 1); }
void CPU::opcode_CB8B() { res_bit(E, 1); }
void CPU::opcode_CB8C() { res_bit(H, 1); }
void CPU::opcode_CB8D() { res_bit(L, 1); }
void CPU::opcode_CB8E() { res_bit(1); }
void CPU::opcode_CB8F() { res_bit(A, 1); }

void CPU::opcode_CB90() { res_bit(B, 2); }
void CPU::opcode_CB91() { res_bit(C, 2); }
void CPU::opcode_CB92() { res_bit(D, 2); }
void CPU::opcode_CB93() { res_bit(E, 2); }
void CPU::opcode_CB94() { res_bit(H, 2); }
void CPU::opcode_CB95() { res_bit(L, 2); }
void CPU::opcode_CB96() { res_bit(2); }
void CPU::opcode_CB97() { res_bit(A, 2); }

void CPU::opcode_CB98() { res_bit(B, 3); }
void CPU::opcode_CB99() { res_bit(C, 3); }
void CPU::opcode_CB9A() { res_bit(D, 3); }
void CPU::opcode_CB9B() { res_bit(E, 3); }
void CPU::opcode_CB9C() { res_bit(H, 3); }
void CPU::opcode_CB9D() { res_bit(L, 3); }
void CPU::opcode_CB9E() { res_bit(3); }
void CPU::opcode_CB9F() { res_bit(A, 3); }

void CPU::opcode_CBA0() { res_bit(B, 4); }
void CPU::opcode_CBA1() { res_bit(C, 4); }
void CPU::opcode_CBA2() { res_bit(D, 4); }
void CPU::opcode_CBA3() { res_bit(E, 4); }
void CPU::opcode_CBA4() { res_bit(H, 4); }
void CPU::opcode_CBA5() { res_bit(L, 4); }
void CPU::opcode_CBA6() { res_bit(4); }
void CPU::opcode_CBA7() { res_bit(A, 4); }

void CPU::opcode_CBA8() { res_bit(B, 5); }
void CPU::opcode_CBA9() { res_bit(C, 5); }
void CPU::opcode_CBAA() { res_bit(D, 5); }
void CPU::opcode_CBAB() { res_bit(E, 5); }
void CPU::opcode_CBAC() { res_bit(H, 5); }
void CPU::opcode_CBAD() { res_bit(L, 5); }
void CPU::opcode_CBAE() { res_bit(5); }
void CPU::opcode_CBAF() { res_bit(A, 5); }

void CPU::opcode_CBB0() { res_bit(B, 6); }
void CPU::opcode_CBB1() { res_bit(C, 6); }
void CPU::opcode_CBB2() { res_bit(D, 6); }
void CPU::opcode_CBB3() { res_bit(E, 6); }
void CPU::opcode_CBB4() { res_bit(H, 6); }
void CPU::opcode_CBB5() { res_bit(L, 6); }
void CPU::opcode_CBB6() { res_bit(6); }
void CPU::opcode_CBB7() { res_bit(A, 6); }

void CPU::opcode_CBB8() { res_bit(B, 7); }
void CPU::opcode_CBB9() { res_bit(C, 7); }
void CPU::opcode_CBBA() { res_bit(D, 7); }
void CPU::opcode_CBBB() { res_bit(E, 7); }
void CPU::opcode_CBBC() { res_bit(H, 7); }
void CPU::opcode_CBBD() { res_bit(L, 7); }
void CPU::opcode_CBBE() { res_bit(7); }
void CPU::opcode_CBBF() { res_bit(A, 7); }

void CPU::opcode_CBC0() { set_bit(B, 0); }
void CPU::opcode_CBC1() { set_bit(C, 0); }
void CPU::opcode_CBC2() { set_bit(D, 0); }
void CPU::opcode_CBC3() { set_bit(E, 0); }
void CPU::opcode_CBC4() { set_bit(H, 0); }
void CPU::opcode_CBC5() { set_bit(L, 0); }
void CPU::opcode_CBC6() { set_bit(0); }
void CPU::opcode_CBC7() { set_bit(A, 0); }

void CPU::opcode_CBC8() { set_bit(B, 1); }
void CPU::opcode_CBC9() { set_bit(C, 1); }
void CPU::opcode_CBCA() { set_bit(D, 1); }
void CPU::opcode_CBCB() { set_bit(E, 1); }
void CPU::opcode_CBCC() { set_bit(H, 1); }
void CPU::opcode_CBCD() { set_bit(L, 1); }
void CPU::opcode_CBCE() { set_bit(1); }
void CPU::opcode_CBCF() { set_bit(A, 1); }

void CPU::opcode_CBD0() { set_bit(B, 2); }
void CPU::opcode_CBD1() { set_bit(C, 2); }
void CPU::opcode_CBD2() { set_bit(D, 2); }
void CPU::opcode_CBD3() { set_bit(E, 2); }
void CPU::opcode_CBD4() { set_bit(H, 2); }
void CPU::opcode_CBD5() { set_bit(L, 2); }
void CPU::opcode_CBD6() { set_bit(2); }
void CPU::opcode_CBD7() { set_bit(A, 2); }

void CPU::opcode_CBD8() { set_bit(B, 3); }
void CPU::opcode_CBD9() { set_bit(C, 3); }
void CPU::opcode_CBDA() { set_bit(D, 3); }
void CPU::opcode_CBDB() { set_bit(E, 3); }
void CPU::opcode_CBDC() { set_bit(H, 3); }
void CPU::opcode_CBDD() { set_bit(L, 3); }
void CPU::opcode_CBDE() { set_bit(3); }
void CPU::opcode_CBDF() { set_bit(A, 3); }

void CPU::opcode_CBE0() { set_bit(B, 4); }
void CPU::opcode_CBE1() { set_bit(C, 4); }
void CPU::opcode_CBE2() { set_bit(D, 4); }
void CPU::opcode_CBE3() { set_bit(E, 4); }
void CPU::opcode_CBE4() { set_bit(H, 4); }
void CPU::opcode_CBE5() { set_bit(L, 4); }
void CPU::opcode_CBE6() { set_bit(4); }
void CPU::opcode_CBE7() { set_bit(A, 4); }

void CPU::opcode_CBE8() { set_bit(B, 5); }
void CPU::opcode_CBE9() { set_bit(C, 5); }
void CPU::opcode_CBEA() { set_bit(D, 5); }
void CPU::opcode_CBEB() { set_bit(E, 5); }
void CPU::opcode_CBEC() { set_bit(H, 5); }
void CPU::opcode_CBED() { set_bit(L, 5); }
void CPU::opcode_CBEE() { set_bit(5); }
void CPU::opcode_CBEF() { set_bit(A, 5); }

void CPU::opcode_CBF0() { set_bit(B, 6); }
void CPU::opcode_CBF1() { set_bit(C, 6); }
void CPU::opcode_CBF2() { set_bit(D, 6); }
void CPU::opcode_CBF3() { set_bit(E, 6); }
void CPU::opcode_CBF4() { set_bit(H, 6); }
void CPU::opcode_CBF5() { set_bit(L, 6); }
void CPU::opcode_CBF6() { set_bit(6); }
void CPU::opcode_CBF7() { set_bit(A, 6); }

void CPU::opcode_CBF8() { set_bit(B, 7); }
void CPU::opcode_CBF9() { set_bit(C, 7); }
void CPU::opcode_CBFA() { set_bit(D, 7); }
void CPU::opcode_CBFB() { set_bit(E, 7); }
void CPU::opcode_CBFC() { set_bit(H, 7); }
void CPU::opcode_CBFD() { set_bit(L, 7); }
void CPU::opcode_CBFE() { set_bit(7); }
void CPU::opcode_CBFF() { set_bit(A, 7); }
