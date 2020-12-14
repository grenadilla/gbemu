#include "cpu.h"

void CPU::opcode_02() { load_reg_to_mem(BC, A); }
void CPU::opcode_06() { load_imm_to_reg(B, RAM[PC + 1]); }
void CPU::opcode_0A() { load_mem_to_reg(A, BC); }
void CPU::opcode_0E() { load_imm_to_reg(C, RAM[PC + 1]); }
void CPU::opcode_12() { load_reg_to_mem(DE, A); }
void CPU::opcode_16() { load_imm_to_reg(D, RAM[PC + 1]); }
void CPU::opcode_1A() { load_mem_to_reg(A, DE); }
void CPU::opcode_22() { load_reg_to_mem_inc(HL, A); }
void CPU::opcode_26() { load_imm_to_reg(H, RAM[PC + 1]); }
void CPU::opcode_2A() { load_mem_to_reg_inc(A, HL); }
void CPU::opcode_2E() { load_imm_to_reg(L, RAM[PC + 1]); }
void CPU::opcode_32() { load_reg_to_mem_dec(HL, A); }
void CPU::opcode_36() { load_imm_to_mem(HL, RAM[PC + 1]); }
void CPU::opcode_3A() { load_mem_to_reg_dec(A, HL); }
void CPU::opcode_3E() { load_imm_to_reg(A, RAM[PC + 1]); }

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

void CPU::opcode_E0() { load_reg_to_upper_mem_imm(RAM[PC + 1], A); }
void CPU::opcode_E2() { load_reg_to_upper_mem_reg(C, A); }
// TODO check endianness, currently is little endian
void CPU::opcode_EA() { load_reg_to_mem_imm( (uint16_t) ((RAM[PC + 2] << 8) | RAM[PC + 1]), A); }
void CPU::opcode_F0() { load_upper_mem_imm_to_reg(A, RAM[PC + 1]); }
void CPU::opcode_F2() { load_upper_mem_reg_to_reg(A, C); }
void CPU::opcode_FA() { load_mem_imm_to_reg(A, (uint16_t) ((RAM[PC + 2] << 8) | RAM[PC + 1])); }
