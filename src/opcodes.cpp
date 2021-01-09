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

void CPU::opcode_CB00() { rlc_reg(B); }
void CPU::opcode_CB01() { rlc_reg(C); }
void CPU::opcode_CB02() { rlc_reg(D); }
void CPU::opcode_CB03() { rlc_reg(E); }
void CPU::opcode_CB04() { rlc_reg(H); }
void CPU::opcode_CB05() { rlc_reg(L); }
void CPU::opcode_CB06() { rlc_mem(); }
void CPU::opcode_CB07() { rlc_reg(A); }

void CPU::opcode_CB08() { rrc_reg(B); }
void CPU::opcode_CB09() { rrc_reg(C); }
void CPU::opcode_CB0A() { rrc_reg(D); }
void CPU::opcode_CB0B() { rrc_reg(E); }
void CPU::opcode_CB0C() { rrc_reg(H); }
void CPU::opcode_CB0D() { rrc_reg(L); }
void CPU::opcode_CB0E() { rrc_mem(); }
void CPU::opcode_CB0F() { rrc_reg(A); }

void CPU::opcode_CB10() { rl_reg(B); }
void CPU::opcode_CB11() { rl_reg(C); }
void CPU::opcode_CB12() { rl_reg(D); }
void CPU::opcode_CB13() { rl_reg(E); }
void CPU::opcode_CB14() { rl_reg(H); }
void CPU::opcode_CB15() { rl_reg(L); }
void CPU::opcode_CB16() { rl_mem(); }
void CPU::opcode_CB17() { rl_reg(A); }

void CPU::opcode_CB18() { rr_reg(B); }
void CPU::opcode_CB19() { rr_reg(C); }
void CPU::opcode_CB1A() { rr_reg(D); }
void CPU::opcode_CB1B() { rr_reg(E); }
void CPU::opcode_CB1C() { rr_reg(H); }
void CPU::opcode_CB1D() { rr_reg(L); }
void CPU::opcode_CB1E() { rr_mem(); }
void CPU::opcode_CB1F() { rr_reg(A); }

void CPU::opcode_CB20() { sla_reg(B); }
void CPU::opcode_CB21() { sla_reg(C); }
void CPU::opcode_CB22() { sla_reg(D); }
void CPU::opcode_CB23() { sla_reg(E); }
void CPU::opcode_CB24() { sla_reg(H); }
void CPU::opcode_CB25() { sla_reg(L); }
void CPU::opcode_CB26() { sla_mem(); }
void CPU::opcode_CB27() { sla_reg(A); }

void CPU::opcode_CB28() { sra_reg(B); }
void CPU::opcode_CB29() { sra_reg(C); }
void CPU::opcode_CB2A() { sra_reg(D); }
void CPU::opcode_CB2B() { sra_reg(E); }
void CPU::opcode_CB2C() { sra_reg(H); }
void CPU::opcode_CB2D() { sra_reg(L); }
void CPU::opcode_CB2E() { sra_mem(); }
void CPU::opcode_CB2F() { sra_reg(A); }

void CPU::opcode_CB30() { swap_reg(B); }
void CPU::opcode_CB31() { swap_reg(C); }
void CPU::opcode_CB32() { swap_reg(D); }
void CPU::opcode_CB33() { swap_reg(E); }
void CPU::opcode_CB34() { swap_reg(H); }
void CPU::opcode_CB35() { swap_reg(L); }
void CPU::opcode_CB36() { swap_mem(); }
void CPU::opcode_CB37() { swap_reg(A); }

void CPU::opcode_CB38() { srl_reg(B); }
void CPU::opcode_CB39() { srl_reg(C); }
void CPU::opcode_CB3A() { srl_reg(D); }
void CPU::opcode_CB3B() { srl_reg(E); }
void CPU::opcode_CB3C() { srl_reg(H); }
void CPU::opcode_CB3D() { srl_reg(L); }
void CPU::opcode_CB3E() { srl_mem(); }
void CPU::opcode_CB3F() { srl_reg(A); }

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

void CPU::opcode_CBC0() { res_bit(B, 0); }
void CPU::opcode_CBC1() { res_bit(C, 0); }
void CPU::opcode_CBC2() { res_bit(D, 0); }
void CPU::opcode_CBC3() { res_bit(E, 0); }
void CPU::opcode_CBC4() { res_bit(H, 0); }
void CPU::opcode_CBC5() { res_bit(L, 0); }
void CPU::opcode_CBC6() { res_bit(0); }
void CPU::opcode_CBC7() { res_bit(A, 0); }

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
