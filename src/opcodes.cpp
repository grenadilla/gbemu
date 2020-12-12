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
