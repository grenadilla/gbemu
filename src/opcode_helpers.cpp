#include "cpu.h"

static const uint8_t MAX_8BIT = 255;
static const uint8_t MAX_4BIT = 15;

uint16_t CPU::retrieve_imm16() {
    return (uint16_t) ((RAM[PC + 2] << 8) | RAM[PC + 1]);
}

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

void CPU::load_imm_to_reg(Register8& reg) {
    reg.set(RAM[PC + 1]);
}

void CPU::load_imm_to_mem(const Register16& ptr) {
    RAM[ptr.get()] = RAM[PC + 1];
}

void CPU::load_reg_to_reg(Register8& reg, const Register8& data) {
    reg.set(data.get());
}

void CPU::load_reg_to_mem_imm(const Register8& data) {
    uint16_t ptr = retrieve_imm16();
    RAM[ptr] = data.get();
}

void CPU::load_mem_imm_to_reg(Register8& reg) {
    uint16_t ptr = retrieve_imm16();
    reg.set(RAM[ptr]);
}

void CPU::load_reg_to_upper_mem_imm(const Register8& data) {
    uint16_t address = 0xff00 | RAM[PC + 1];
    RAM[address] = data.get();
}

void CPU::load_upper_mem_imm_to_reg(Register8& reg) {
    uint16_t address = 0xff00 | RAM[PC + 1];
    reg.set(RAM[address]);
}

void CPU::load_reg_to_upper_mem_reg(Register8& upper_ptr, Register8& data) {
    uint16_t address = 0xff00 | upper_ptr.get();
    RAM[address] = data.get();
}

void CPU::load_upper_mem_reg_to_reg(Register8& reg, Register8& upper_ptr) {
    uint16_t address = 0xff00 | upper_ptr.get();
    reg.set(RAM[address]);
}

void CPU::load_imm_to_reg16(Register16& reg) {
    uint16_t imm = retrieve_imm16();
    reg.set(imm);
}

void CPU::load_sp_to_mem() {
    uint16_t ptr = retrieve_imm16();
    RAM[ptr] = SP & 0x00FF;
    RAM[ptr] = (SP & 0xFF00) >> 8;
}

void CPU::inc_reg8(Register8& reg) {
    F.set_zero(reg.get() == MAX_8BIT);
    F.set_subtract(false);
    F.set_half_carry(reg.get() == MAX_4BIT);

    reg.set(reg.get() + 1);
}

void CPU::inc_reg16(Register16& reg) {
    // No flags for these
    reg.set(reg.get() + 1);
}

void CPU::inc_mem(const Register16& ptr) {
    uint8_t val = RAM[ptr.get()];
    F.set_zero(val == MAX_8BIT);
    F.set_subtract(false);
    F.set_half_carry(val == MAX_4BIT);

    RAM[ptr.get()] = val + 1;
}

void CPU::dec_reg8(Register8& reg) {
    F.set_zero(reg.get() == 1);
    F.set_subtract(true);
    F.set_half_carry(reg.get() == MAX_4BIT + 1);

    reg.set(reg.get() - 1);
}

void CPU::dec_reg16(Register16& reg) {
    // No flags for these
    reg.set(reg.get() - 1);
}

void CPU::dec_mem(const Register16& ptr) {
    uint8_t val = RAM[ptr.get()];
    F.set_zero(val == 1);
    F.set_subtract(true);
    F.set_half_carry(val == MAX_4BIT + 1);

    RAM[ptr.get()] = val - 1;
}
