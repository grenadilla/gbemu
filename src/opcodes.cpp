#include "cpu.h"

// Loads
void CPU::opcode_02() { load_reg_to_mem(BC, A); }
void CPU::opcode_06() { load_imm_to_reg(B); }
void CPU::opcode_0A() { load_mem_to_reg(A, BC); }
void CPU::opcode_0E() { load_imm_to_reg(C); }
void CPU::opcode_12() { load_reg_to_mem(DE, A); }
void CPU::opcode_16() { load_imm_to_reg(D); }
void CPU::opcode_1A() { load_mem_to_reg(A, DE); }
void CPU::opcode_22() { load_reg_to_mem_inc(A); }
void CPU::opcode_26() { load_imm_to_reg(H); }
void CPU::opcode_2A() { load_mem_to_reg_inc(A); }
void CPU::opcode_2E() { load_imm_to_reg(L); }
void CPU::opcode_32() { load_reg_to_mem_dec(A); }
void CPU::opcode_36() { load_imm_to_mem(); }
void CPU::opcode_3A() { load_mem_to_reg_dec(A); }
void CPU::opcode_3E() { load_imm_to_reg(A); }

void CPU::opcode_40() { load_reg_to_reg(B, B); }
void CPU::opcode_41() { load_reg_to_reg(B, C); }
void CPU::opcode_42() { load_reg_to_reg(B, D); }
void CPU::opcode_43() { load_reg_to_reg(B, E); }
void CPU::opcode_44() { load_reg_to_reg(B, H); }
void CPU::opcode_45() { load_reg_to_reg(B, L); }
void CPU::opcode_46() { load_mem_to_reg(B, HL); }
void CPU::opcode_47() { load_reg_to_reg(B, A); }

void CPU::opcode_48() { load_reg_to_reg(C, B); }
void CPU::opcode_49() { load_reg_to_reg(C, C); }
void CPU::opcode_4A() { load_reg_to_reg(C, D); }
void CPU::opcode_4B() { load_reg_to_reg(C, E); }
void CPU::opcode_4C() { load_reg_to_reg(C, H); }
void CPU::opcode_4D() { load_reg_to_reg(C, L); }
void CPU::opcode_4E() { load_mem_to_reg(C, HL); }
void CPU::opcode_4F() { load_reg_to_reg(C, A); }

void CPU::opcode_50() { load_reg_to_reg(D, B); }
void CPU::opcode_51() { load_reg_to_reg(D, C); }
void CPU::opcode_52() { load_reg_to_reg(D, D); }
void CPU::opcode_53() { load_reg_to_reg(D, E); }
void CPU::opcode_54() { load_reg_to_reg(D, H); }
void CPU::opcode_55() { load_reg_to_reg(D, L); }
void CPU::opcode_56() { load_mem_to_reg(D, HL); }
void CPU::opcode_57() { load_reg_to_reg(D, A); }

void CPU::opcode_58() { load_reg_to_reg(E, B); }
void CPU::opcode_59() { load_reg_to_reg(E, C); }
void CPU::opcode_5A() { load_reg_to_reg(E, D); }
void CPU::opcode_5B() { load_reg_to_reg(E, E); }
void CPU::opcode_5C() { load_reg_to_reg(E, H); }
void CPU::opcode_5D() { load_reg_to_reg(E, L); }
void CPU::opcode_5E() { load_mem_to_reg(E, HL); }
void CPU::opcode_5F() { load_reg_to_reg(E, A); }

void CPU::opcode_60() { load_reg_to_reg(H, B); }
void CPU::opcode_61() { load_reg_to_reg(H, C); }
void CPU::opcode_62() { load_reg_to_reg(H, D); }
void CPU::opcode_63() { load_reg_to_reg(H, E); }
void CPU::opcode_64() { load_reg_to_reg(H, H); }
void CPU::opcode_65() { load_reg_to_reg(H, L); }
void CPU::opcode_66() { load_mem_to_reg(H, HL); }
void CPU::opcode_67() { load_reg_to_reg(H, A); }

void CPU::opcode_68() { load_reg_to_reg(L, B); }
void CPU::opcode_69() { load_reg_to_reg(L, C); }
void CPU::opcode_6A() { load_reg_to_reg(L, D); }
void CPU::opcode_6B() { load_reg_to_reg(L, E); }
void CPU::opcode_6C() { load_reg_to_reg(L, H); }
void CPU::opcode_6D() { load_reg_to_reg(L, L); }
void CPU::opcode_6E() { load_mem_to_reg(L, HL); }
void CPU::opcode_6F() { load_reg_to_reg(L, A); }

void CPU::opcode_70() { load_reg_to_mem(HL, B); }
void CPU::opcode_71() { load_reg_to_mem(HL, C); }
void CPU::opcode_72() { load_reg_to_mem(HL, D); }
void CPU::opcode_73() { load_reg_to_mem(HL, E); }
void CPU::opcode_74() { load_reg_to_mem(HL, H); }
void CPU::opcode_75() { load_reg_to_mem(HL, L); }
// Skip opcode_76 which is HALT
void CPU::opcode_77() { load_reg_to_mem(HL, A); }

void CPU::opcode_78() { load_reg_to_reg(A, B); }
void CPU::opcode_79() { load_reg_to_reg(A, C); }
void CPU::opcode_7A() { load_reg_to_reg(A, D); }
void CPU::opcode_7B() { load_reg_to_reg(A, E); }
void CPU::opcode_7C() { load_reg_to_reg(A, H); }
void CPU::opcode_7D() { load_reg_to_reg(A, L); }
void CPU::opcode_7E() { load_mem_to_reg(A, HL); }
void CPU::opcode_7F() { load_reg_to_reg(A, A); }

void CPU::opcode_E0() { load_reg_to_upper_mem_imm(A); }
void CPU::opcode_E2() { load_reg_to_upper_mem_reg(C, A); }
// TODO check endianness, currently is little endian
void CPU::opcode_EA() { load_reg_to_mem_imm(A); }
void CPU::opcode_F0() { load_upper_mem_imm_to_reg(A); }
void CPU::opcode_F2() { load_upper_mem_reg_to_reg(A, C); }
void CPU::opcode_FA() { load_mem_imm_to_reg(A); }

void CPU::opcode_01() { load_imm_to_reg16(BC); }
void CPU::opcode_11() { load_imm_to_reg16(DE); }
void CPU::opcode_21() { load_imm_to_reg16(HL); }
void CPU::opcode_31() { SP = retrieve_imm16(); }
void CPU::opcode_08() { load_sp_to_mem(); }

// Increments and decrements
void CPU::opcode_03() { inc_reg16(BC); }
void CPU::opcode_13() { inc_reg16(DE); }
void CPU::opcode_23() { inc_reg16(HL); }
void CPU::opcode_33() { SP++; }
void CPU::opcode_04() { inc_reg8(B); }
void CPU::opcode_14() { inc_reg8(D); }
void CPU::opcode_24() { inc_reg8(H); }
void CPU::opcode_34() { inc_mem(); }
void CPU::opcode_05() { dec_reg8(B); }
void CPU::opcode_15() { dec_reg8(D); }
void CPU::opcode_25() { dec_reg8(H); }
void CPU::opcode_35() { dec_mem(); }
void CPU::opcode_0B() { dec_reg16(BC); }
void CPU::opcode_1B() { dec_reg16(DE); }
void CPU::opcode_2B() { dec_reg16(HL); }
void CPU::opcode_3B() { SP--; }
void CPU::opcode_0C() { inc_reg8(C); }
void CPU::opcode_1C() { inc_reg8(E); }
void CPU::opcode_2C() { inc_reg8(L); }
void CPU::opcode_3C() { inc_reg8(A); }
void CPU::opcode_0D() { dec_reg8(C); }
void CPU::opcode_1D() { dec_reg8(E); }
void CPU::opcode_2D() { dec_reg8(L); }
void CPU::opcode_3D() { dec_reg8(A); }

// Arithmetic
void CPU::opcode_80() { add_reg(B); }
void CPU::opcode_81() { add_reg(C); }
void CPU::opcode_82() { add_reg(D); }
void CPU::opcode_83() { add_reg(E); }
void CPU::opcode_84() { add_reg(H); }
void CPU::opcode_85() { add_reg(L); }
void CPU::opcode_86() { add_mem(); }
void CPU::opcode_87() { add_reg(A); }
void CPU::opcode_88() { addc_reg(B); }
void CPU::opcode_89() { addc_reg(C); }
void CPU::opcode_8A() { addc_reg(D); }
void CPU::opcode_8B() { addc_reg(E); }
void CPU::opcode_8C() { addc_reg(H); }
void CPU::opcode_8D() { addc_reg(L); }
void CPU::opcode_8E() { addc_mem(); }
void CPU::opcode_8F() { addc_reg(A); }

void CPU::opcode_90() { sub_reg(B); }
void CPU::opcode_91() { sub_reg(C); }
void CPU::opcode_92() { sub_reg(D); }
void CPU::opcode_93() { sub_reg(E); }
void CPU::opcode_94() { sub_reg(H); }
void CPU::opcode_95() { sub_reg(L); }
void CPU::opcode_96() { sub_mem(); }
void CPU::opcode_97() { sub_reg(A); }
void CPU::opcode_98() { subc_reg(B); }
void CPU::opcode_99() { subc_reg(C); }
void CPU::opcode_9A() { subc_reg(D); }
void CPU::opcode_9B() { subc_reg(E); }
void CPU::opcode_9C() { subc_reg(H); }
void CPU::opcode_9D() { subc_reg(L); }
void CPU::opcode_9E() { subc_mem(); }
void CPU::opcode_9F() { subc_reg(A); }

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
void CPU::opcode_A0() { and_reg(B); }
void CPU::opcode_A1() { and_reg(C); }
void CPU::opcode_A2() { and_reg(D); }
void CPU::opcode_A3() { and_reg(E); }
void CPU::opcode_A4() { and_reg(H); }
void CPU::opcode_A5() { and_reg(L); }
void CPU::opcode_A6() { and_mem(); }
void CPU::opcode_A7() { and_reg(A); }

void CPU::opcode_A8() { xor_reg(B); }
void CPU::opcode_A9() { xor_reg(C); }
void CPU::opcode_AA() { xor_reg(D); }
void CPU::opcode_AB() { xor_reg(E); }
void CPU::opcode_AC() { xor_reg(H); }
void CPU::opcode_AD() { xor_reg(L); }
void CPU::opcode_AE() { xor_mem(); }
void CPU::opcode_AF() { xor_reg(A); }

void CPU::opcode_B0() { or_reg(B); }
void CPU::opcode_B1() { or_reg(C); }
void CPU::opcode_B2() { or_reg(D); }
void CPU::opcode_B3() { or_reg(E); }
void CPU::opcode_B4() { or_reg(H); }
void CPU::opcode_B5() { or_reg(L); }
void CPU::opcode_B6() { or_mem(); }
void CPU::opcode_B7() { or_reg(A); }

// Compare
void CPU::opcode_B8() { cp_reg(B); }
void CPU::opcode_B9() { cp_reg(C); }
void CPU::opcode_BA() { cp_reg(D); }
void CPU::opcode_BB() { cp_reg(E); }
void CPU::opcode_BC() { cp_reg(H); }
void CPU::opcode_BD() { cp_reg(L); }
void CPU::opcode_BE() { cp_mem(); }
void CPU::opcode_BF() { cp_reg(A); }

// Stack
void CPU::opcode_C1() { pop_stack(BC); }
void CPU::opcode_D1() { pop_stack(DE); }
void CPU::opcode_E1() { pop_stack(HL); }
void CPU::opcode_F1() { pop_stack(AF); }
void CPU::opcode_C5() { push_stack(BC); }
void CPU::opcode_D5() { push_stack(DE); }
void CPU::opcode_E5() { push_stack(HL); }
void CPU::opcode_F5() { push_stack(AF); }
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
//void CPU::opcode_D9() {}

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
