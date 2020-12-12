#include "cpu.h"

CPU::Opcode CPU::opcode_table[] = {0};
CPU::Opcode CPU::opcode_prefixed_table[] = {0};


void CPU::load_reg_to_mem(const Register16& ptr, const Register8& data) {
    RAM[ptr.get()] = data.get();
}

void CPU::load_reg_to_mem_inc(Register16& ptr, const Register8& data) {
    uint16_t address = ptr.get();
    RAM[address] = data.get();
    ptr.set(address + 1);
}

void CPU::load_reg_to_mem_dec(Register16& ptr, const Register8& data) {
    uint16_t address = ptr.get();
    RAM[address] = data.get();
    ptr.set(address - 1);
}

void CPU::load_mem_to_reg(Register8& reg, const Register16& ptr) {
    reg.set(RAM[ptr.get()]);
}

void CPU::load_mem_to_reg_inc(Register8& reg, Register16& ptr) {
    uint16_t address = ptr.get();
    reg.set(RAM[address]);
    ptr.set(address + 1);
}

void CPU::load_mem_to_reg_dec(Register8& reg, Register16& ptr) {
    uint16_t address = ptr.get();
    reg.set(RAM[address]);
    ptr.set(address - 1);
}

void CPU::load_imm_to_reg(Register8& reg, uint8_t imm) {
    reg.set(imm);
}

void CPU::load_imm_to_mem(const Register16& ptr, uint8_t imm) {
    RAM[ptr.get()] = imm;
}

void CPU::load_reg_to_reg(Register8& reg, const Register8& data) {
    reg.set(data.get());
}
