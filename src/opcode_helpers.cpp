#include "cpu.h"

static const uint8_t MAX_8BIT = 255;
static const uint8_t MAX_4BIT = 15;

uint16_t CPU::retrieve_imm16() {
    return static_cast<uint16_t>((RAM[PC + 2] << 8) | RAM[PC + 1]);
}

void CPU::load_reg_to_mem(const Register16& ptr, const Register8& data) {
    RAM[ptr.get()] = data.get();
}

void CPU::load_reg_to_mem_inc(const Register8& data) {
    uint16_t address = HL.get();
    RAM[address] = data.get();
    HL.set(address + 1);
}

void CPU::load_reg_to_mem_dec(const Register8& data) {
    uint16_t address = HL.get();
    RAM[address] = data.get();
    HL.set(address - 1);
}

void CPU::load_mem_to_reg(Register8& reg, const Register16& ptr) {
    reg.set(RAM[ptr.get()]);
}

void CPU::load_mem_to_reg_inc(Register8& reg) {
    uint16_t address = HL.get();
    reg.set(RAM[address]);
    HL.set(address + 1);
}

void CPU::load_mem_to_reg_dec(Register8& reg) {
    uint16_t address = HL.get();
    reg.set(RAM[address]);
    HL.set(address - 1);
}

void CPU::load_imm_to_reg(Register8& reg) {
    reg.set(RAM[PC + 1]);
}

void CPU::load_imm_to_mem() {
    RAM[HL.get()] = RAM[PC + 1];
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

void CPU::inc_mem() {
    uint8_t val = RAM[HL.get()];
    F.set_zero(val == MAX_8BIT);
    F.set_subtract(false);
    F.set_half_carry(val == MAX_4BIT);

    RAM[HL.get()] = val + 1;
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

void CPU::dec_mem() {
    uint8_t val = RAM[HL.get()];
    F.set_zero(val == 1);
    F.set_subtract(true);
    F.set_half_carry(val == MAX_4BIT + 1);

    RAM[HL.get()] = val - 1;
}

void CPU::add(Register8& dest, uint8_t val) {
    F.set_subtract(false);
    F.set_half_carry(((dest.get() & 0x0F) + (val & 0x0F)) & 0x10);
    uint8_t result = dest.get() + val;
    F.set_carry(result < dest.get() && result < val);
    F.set_zero(result == 0);
    dest.set(result);
}

void CPU::add_reg(const Register8& reg) {
    add(A, reg.get());
}

void CPU::add_mem() {
    add(A, RAM[HL.get()]);
}

void CPU::add_imm() {
    add(A, RAM[PC + 1]);
}

void CPU::addc(Register8& dest, uint8_t val) {
    bool carry = F.get_carry();
    F.set_subtract(false);
    F.set_half_carry(((dest.get() & 0x0F) + (val & 0x0F) + carry) & 0x10);
    uint8_t result = dest.get() + val + carry;
    F.set_carry(result < dest.get() && result < val);
    F.set_zero(result == 0);
    dest.set(result);
}

void CPU::addc_reg(const Register8& reg) {
    addc(A, reg.get());
}

void CPU::addc_mem() {
    addc(A, RAM[HL.get()]);
}

void CPU::addc_imm() {
    addc(A, RAM[PC + 1]);
}

void CPU::sub(Register8& dest, uint8_t val) {
    F.set_subtract(true);
    F.set_half_carry((dest.get() & 0x0F) < (val & 0x0F));
    F.set_carry(dest.get() < val);
    uint8_t result = dest.get() - val;
    F.set_zero(result == 0);
    dest.set(result);
}

void CPU::sub_reg(const Register8& reg) {
    sub(A, reg.get());
}

void CPU::sub_mem() {
    sub(A, RAM[HL.get()]);
}

void CPU::sub_imm() {
    sub(A, RAM[PC + 1]);
}

void CPU::subc(Register8& dest, uint8_t val) {
    bool carry = F.get_carry();
    F.set_subtract(true);
    F.set_half_carry((dest.get() & 0x0F) < (val & 0x0F) + carry);
    F.set_carry(dest.get() < val + carry);
    uint8_t result = dest.get() - val - carry;
    F.set_zero(result == 0);
    dest.set(result);
}

void CPU::subc_reg(const Register8& reg) {
    subc(A, reg.get());
}

void CPU::subc_mem() {
    subc(A, RAM[HL.get()]);
}

void CPU::subc_imm() {
    subc(A, RAM[PC + 1]);
}

void CPU::add_HL(const Register16& reg) {
    add(L, reg.get_low());
    add(H, reg.get_high());
}

void CPU::add_HL(uint16_t val) {
    add(L, val & 0x00FF);
    add(H, (val & 0xFF00) >> 8);
}

void CPU::add_SP() {
    // Uses signed two's complement
    int8_t val = static_cast<int8_t>(RAM[PC + 1]);

    F.set_zero(false);
    F.set_subtract(false);
    uint8_t lower_sp = SP & 0xFF;
    F.set_half_carry(((lower_sp & 0x0F) + (val & 0x0F)) & 0x10);
    uint8_t lower_result = lower_sp + val;
    F.set_carry(lower_result < lower_sp && lower_result < val);

    SP += val;
}

void CPU::and_reg(const Register8& reg) {
    A.set(A.get() & reg.get());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(true);
    F.set_carry(false);
}

void CPU::and_mem() {
    A.set(A.get() & RAM[HL.get()]);
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(true);
    F.set_carry(false);
}

void CPU::xor_reg(const Register8& reg) {
    A.set(A.get() ^ reg.get());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::xor_mem() {
    A.set(A.get() ^ RAM[HL.get()]);
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::or_reg(const Register8& reg) {
    A.set(A.get() | reg.get());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::or_mem() {
    A.set(A.get() | RAM[HL.get()]);
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::cp_reg(const Register8& reg) {
    uint8_t before = A.get();
    sub_reg(reg);
    A.set(before);
}

void CPU::cp_mem() {
    uint8_t before = A.get();
    sub_mem();
    A.set(before);
}

void CPU::load_HL() {
    // Uses signed two's complement
    int8_t val = static_cast<int8_t>(RAM[PC + 1]);

    F.set_zero(false);
    F.set_subtract(false);
    uint8_t lower_sp = SP & 0xFF;
    F.set_half_carry(((lower_sp & 0x0F) + (val & 0x0F)) & 0x10);
    uint8_t lower_result = lower_sp + val;
    F.set_carry(lower_result < lower_sp && lower_result < val);

    HL.set(SP + val);
}

void CPU::pop_stack(Register16& reg) {
    uint8_t lower = RAM[SP];
    SP += sizeof(uint8_t);
    uint8_t upper = RAM[SP];
    SP += sizeof(uint8_t);
    reg.set(upper, lower);
}

void CPU::push_stack(Register16& reg) {
    SP -= sizeof(uint8_t);
    RAM[SP] = reg.get_high();
    SP -= sizeof(uint8_t);
    RAM[SP] = reg.get_low();
}

void CPU::load_SP() {
    SP = HL.get();
}

void CPU::jump(uint16_t pos) {
    jump_taken = true;
    PC = pos;
}

void CPU::call(bool condition) {
    if (condition) {
        jump_taken = true;
        PC = retrieve_imm16();
        SP -= sizeof(uint8_t);

        // CALL instruction is 3 bytes long
        uint16_t next_instr = PC + 3 * sizeof(uint8_t);
        RAM[SP] = (next_instr & 0xFF00) >> 8;
        SP -= sizeof(uint8_t);
        RAM[SP] = next_instr & 0x00FF;
    }
}

void CPU::ret(bool condition) {
    if (condition) {
        uint8_t lower = RAM[SP];
        SP += sizeof(uint8_t);
        uint8_t upper = RAM[SP];
        SP += sizeof(uint8_t);
        PC = (upper << 8) & lower;
        jump_taken = true;
    }
}

void CPU::jr(bool condition) {
    if (condition) {
        int8_t val = static_cast<int8_t>(RAM[PC + 1]);
        jump(PC + val);
    }
}

void CPU::jp(bool condition) {
    if (condition) {
        jump(retrieve_imm16());
    }
}

void CPU::jp_mem() {
    jump(HL.get());
}
