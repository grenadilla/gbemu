#include "cpu.h"

static const uint8_t MAX_8BIT = 255;
static const uint8_t MAX_4BIT = 15;

void CPU::opcode_illegal() {}

void CPU::load_reg(Register8& reg, const Register8& data) {
    reg.set(data.get());
}

void CPU::load_reg(const Register16& ptr, const Register8& data) {
    mem->write(ptr.get(), data.get());
}

void CPU::load_reg_inc(const Register8& data) {
    uint16_t address = HL.get();
    mem->write(address, data.get());
    HL.set(address + 1);
}

void CPU::load_reg_dec(const Register8& data) {
    uint16_t address = HL.get();
    mem->write(address, data.get());
    HL.set(address - 1);
}

void CPU::load_mem(Register8& reg, const Register16& ptr) {
    reg.set(mem->read(ptr.get()));
}

void CPU::load_mem_inc(Register8& reg) {
    uint16_t address = HL.get();
    reg.set(mem->read(address));
    HL.set(address + 1);
}

void CPU::load_mem_dec(Register8& reg) {
    uint16_t address = HL.get();
    reg.set(mem->read(address));
    HL.set(address - 1);
}

void CPU::load_imm(Register8& reg) {
    reg.set(retrieve_imm8());
}

void CPU::load_imm(Register16& reg) {
    uint16_t imm = retrieve_imm16();
    reg.set(imm);
}

void CPU::load_imm() {
    mem->write(HL.get(), retrieve_imm8());
}

void CPU::load_reg_to_mem_imm(const Register8& data) {
    uint16_t ptr = retrieve_imm16();
    mem->write(ptr, data.get());
}

void CPU::load_mem_imm_to_reg(Register8& reg) {
    uint16_t ptr = retrieve_imm16();
    reg.set(mem->read(ptr));
}

void CPU::load_reg_to_upper_mem_imm(const Register8& data) {
    uint16_t address = 0xff00 | retrieve_imm8();
    mem->write(address, data.get());
}

void CPU::load_upper_mem_imm_to_reg(Register8& reg) {
    uint16_t address = 0xff00 | retrieve_imm8();
    reg.set(mem->read(address));
}

void CPU::load_reg_to_upper_mem_reg(Register8& upper_ptr, Register8& data) {
    uint16_t address = 0xff00 | upper_ptr.get();
    mem->write(address, data.get());
}

void CPU::load_upper_mem_reg_to_reg(Register8& reg, Register8& upper_ptr) {
    uint16_t address = 0xff00 | upper_ptr.get();
    reg.set(mem->read(address));
}

void CPU::load_sp() {
    uint16_t ptr = retrieve_imm16();
    mem->write(ptr, SP & 0x00FF);
    mem->write(ptr, (SP & 0xFF00) >> 8);
}

void CPU::inc(Register8& reg) {
    F.set_zero(reg.get() == MAX_8BIT);
    F.set_subtract(false);
    F.set_half_carry(reg.get() == MAX_4BIT);

    reg.set(reg.get() + 1);
}

void CPU::inc(Register16& reg) {
    // No flags for these
    reg.set(reg.get() + 1);
}

void CPU::inc() {
    uint8_t val = mem->read(HL.get());
    F.set_zero(val == MAX_8BIT);
    F.set_subtract(false);
    F.set_half_carry(val == MAX_4BIT);

    mem->write(HL.get(), val + 1);
}

void CPU::dec(Register8& reg) {
    F.set_zero(reg.get() == 1);
    F.set_subtract(true);
    F.set_half_carry(reg.get() == MAX_4BIT + 1);

    reg.set(reg.get() - 1);
}

void CPU::dec(Register16& reg) {
    // No flags for these
    reg.set(reg.get() - 1);
}

void CPU::dec() {
    uint8_t val = mem->read(HL.get());
    F.set_zero(val == 1);
    F.set_subtract(true);
    F.set_half_carry(val == MAX_4BIT + 1);

    mem->write(HL.get(), val - 1);
}

void CPU::add(Register8& dest, uint8_t val) {
    F.set_subtract(false);
    F.set_half_carry(((dest.get() & 0x0F) + (val & 0x0F)) & 0x10);
    uint8_t result = dest.get() + val;
    F.set_carry(result < dest.get() && result < val);
    F.set_zero(result == 0);
    dest.set(result);
}

void CPU::add(const Register8& reg) {
    add(A, reg.get());
}

void CPU::add() {
    add(A, mem->read(HL.get()));
}

void CPU::add_imm() {
    add(A, retrieve_imm8());
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

void CPU::addc(const Register8& reg) {
    addc(A, reg.get());
}

void CPU::addc() {
    addc(A, mem->read(HL.get()));
}

void CPU::addc_imm() {
    addc(A, retrieve_imm8());
}

void CPU::sub(Register8& dest, uint8_t val) {
    F.set_subtract(true);
    F.set_half_carry((dest.get() & 0x0F) < (val & 0x0F));
    F.set_carry(dest.get() < val);
    uint8_t result = dest.get() - val;
    F.set_zero(result == 0);
    dest.set(result);
}

void CPU::sub(const Register8& reg) {
    sub(A, reg.get());
}

void CPU::sub() {
    sub(A, mem->read(HL.get()));
}

void CPU::sub_imm() {
    sub(A, retrieve_imm8());
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

void CPU::subc(const Register8& reg) {
    subc(A, reg.get());
}

void CPU::subc() {
    subc(A, mem->read(HL.get()));
}

void CPU::subc_imm() {
    subc(A, retrieve_imm8());
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
    int8_t val = static_cast<int8_t>(mem->read(PC + 1));

    F.set_zero(false);
    F.set_subtract(false);
    uint8_t lower_sp = SP & 0xFF;
    F.set_half_carry(((lower_sp & 0x0F) + (val & 0x0F)) & 0x10);
    uint8_t lower_result = lower_sp + val;
    F.set_carry(lower_result < lower_sp && lower_result < val);

    SP += val;
}

void CPU::op_and(const Register8& reg) {
    A.set(A.get() & reg.get());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(true);
    F.set_carry(false);
}

void CPU::op_and() {
    A.set(A.get() & mem->read(HL.get()));
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(true);
    F.set_carry(false);
}

void CPU::op_and_imm() {
    A.set(A.get() & retrieve_imm8());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(true);
    F.set_carry(false);
}

void CPU::op_xor(const Register8& reg) {
    A.set(A.get() ^ reg.get());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::op_xor() {
    A.set(A.get() ^ mem->read(HL.get()));
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::op_xor_imm() {
    A.set(A.get() ^ retrieve_imm8());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);

}

void CPU::op_or(const Register8& reg) {
    A.set(A.get() | reg.get());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::op_or() {
    A.set(A.get() | mem->read(HL.get()));
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::op_or_imm() {
    A.set(A.get() | retrieve_imm8());
    F.set_zero(A.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::cp(const Register8& reg) {
    uint8_t before = A.get();
    sub(reg);
    A.set(before);
}

void CPU::cp() {
    uint8_t before = A.get();
    sub();
    A.set(before);
}

void CPU::cp_imm() {
    uint8_t before = A.get();
    sub_imm();
    A.set(before);
}

void CPU::load_HL() {
    // Uses signed two's complement
    int8_t val = static_cast<int8_t>(mem->read(PC + 1));

    F.set_zero(false);
    F.set_subtract(false);
    uint8_t lower_sp = SP & 0xFF;
    F.set_half_carry(((lower_sp & 0x0F) + (val & 0x0F)) & 0x10);
    uint8_t lower_result = lower_sp + val;
    F.set_carry(lower_result < lower_sp && lower_result < val);

    HL.set(SP + val);
}

void CPU::pop(Register16& reg) {
    reg.set(pop_stack());
}

void CPU::push(Register16& reg) {
    push_stack(reg.get());
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
        push_stack(PC + 1);
    }
}

void CPU::ret(bool condition) {
    if (condition) {
        PC = pop_stack();
        jump_taken = true;
    }
}

void CPU::jr(bool condition) {
    if (condition) {
        int8_t val = static_cast<int8_t>(retrieve_imm8());
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

void CPU::rst(uint8_t val) {
    jump_taken = true;
    push_stack(PC);
    PC = val * 0x08;
}

void CPU::daa() {
    // From https://forums.nesdev.com/viewtopic.php?t=15944
    if (!F.get_subtract()) {  
        // after an addition, adjust if (half-)carry occurred or if result is out of bounds
        if (F.get_carry() || A.get() > 0x99) { 
            A.set(A.get() + 0x60);
            F.set_carry(true);
        }
        if (F.get_half_carry() || (A.get() & 0x0F) > 0x09) {
            A.set(A.get() + 0x06);
            F.set_carry(false);
        }
    } else {  
        // after a subtraction, only adjust if (half-)carry occurred
        if (F.get_carry()) {
            A.set(A.get() - 0x60);
            F.set_carry(false);
        }
        if (F.get_half_carry()) {
            A.set(A.get() - 0x06);
            F.set_carry(false);
        }
    }
    // these flags are always updated
    F.set_zero(A.get() == 0);
    F.set_half_carry(false);
}

void CPU::scf() {
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(true);
}

void CPU::cpl() {
    A.set(~A.get());
    F.set_subtract(true);
    F.set_half_carry(true);
}

void CPU::ccf() {
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(!F.get_half_carry());
}

uint8_t CPU::rlc(uint8_t val) {
    uint8_t bit7 = (val & 0x80) >> 7;
    uint8_t result = (val << 1) | bit7;
    F.set_carry(bit7);
    F.set_zero(result == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    return result;
}

uint8_t CPU::rl(uint8_t val) {
    uint8_t bit7 = (val & 0x80) >> 7;
    uint8_t result = (val << 1) | F.get_carry();
    F.set_carry(bit7);
    F.set_zero(result == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    return result;
}

uint8_t CPU::rrc(uint8_t val) {
    uint8_t bit0 = val & 0x01;
    uint8_t result = (val >> 1) | (bit0 << 7);
    F.set_carry(bit0);
    F.set_zero(result == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    return result;
}

uint8_t CPU::rr(uint8_t val) {
    uint8_t bit0 = val & 0x01;
    uint8_t result = (val >> 1) | (F.get_carry() << 7);
    F.set_carry(bit0);
    F.set_zero(result == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    return result;
}

void CPU::rlc_a() {
    A.set(rlc(A.get()));
    F.set_zero(false);
}

void CPU::rl_a() {
    A.set(rl(A.get()));
    F.set_zero(false);
}

void CPU::rrc_a() {
    A.set(rrc(A.get()));
    F.set_zero(false);
}

void CPU::rr_a() {
    A.set(rr(A.get()));
    F.set_zero(false);
}

void CPU::rlc(Register8& reg) {
    reg.set(rlc(reg.get()));
}

void CPU::rl(Register8& reg) {
    reg.set(rl(reg.get()));
}

void CPU::rrc(Register8& reg) {
    reg.set(rrc(reg.get()));
}

void CPU::rr(Register8& reg) {
    reg.set(rr(reg.get()));
}

void CPU::rlc() {
    mem->write(HL.get(), rlc(mem->read(HL.get())));
}

void CPU::rl() {
    mem->write(HL.get(), rl(mem->read(HL.get())));
}

void CPU::rrc() {
    mem->write(HL.get(), rrc(mem->read(HL.get())));
}

void CPU::rr() {
    mem->write(HL.get(), rr(mem->read(HL.get())));
}

void CPU::sla(Register8& reg) {
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(reg.get() & 0x80);
    reg.set(reg.get() << 1);
    F.set_zero(reg.get() == 0);
}

void CPU::sla() {
    uint8_t val = mem->read(HL.get());
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(val & 0x80);
    val = val << 1;
    F.set_zero(val == 0);
    mem->write(HL.get(), val);
}

void CPU::sra(Register8& reg) {
    uint8_t val = static_cast<int8_t>(reg.get());
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(val & 0x01);
    // Ensure arithmetic shift
    val = val < 0 ? ~(~val >> 1) : val >> 1;
    F.set_zero(val == 0);
    reg.set(static_cast<uint8_t>(val));
}

void CPU::sra() {
    uint8_t val = static_cast<int8_t>(mem->read(HL.get()));
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(val & 0x01);
    // Ensure arithmetic shift
    val = val < 0 ? ~(~val >> 1) : val >> 1;
    F.set_zero(val == 0);
    mem->write(HL.get(), static_cast<uint8_t>(val));
}

void CPU::swap(Register8& reg) {
    uint8_t new_upper = (reg.get() & 0x0F) << 4;
    uint8_t new_lower = (reg.get() & 0xF0) >> 4;
    reg.set(new_upper | new_lower);
    F.set_zero(reg.get() == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::swap() {
    uint8_t val = mem->read(HL.get());
    uint8_t new_upper = (val & 0x0F) << 4;
    uint8_t new_lower = (val & 0xF0) >> 4;
    mem->write(HL.get(), new_upper | new_lower);
    F.set_zero(val == 0);
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(false);
}

void CPU::srl(Register8& reg) {
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(reg.get() & 0x01);
    reg.set(reg.get() >> 1);
    F.set_zero(reg.get() == 0);
}

void CPU::srl() {
    uint8_t val = mem->read(HL.get());
    F.set_subtract(false);
    F.set_half_carry(false);
    F.set_carry(val & 0x01);
    val = val >> 1;
    F.set_zero(val == 0);
    mem->write(HL.get(), val);
}

void CPU::test_bit(const Register8& reg, uint8_t bit_num) {
    uint8_t mask = 1 << bit_num;
    F.set_zero(reg.get() & mask);
    F.set_subtract(false);
    F.set_half_carry(true);
}

void CPU::test_bit(uint8_t bit_num) {
    uint8_t mask = 1 << bit_num;
    F.set_zero(mem->read(HL.get()) & mask);
    F.set_subtract(false);
    F.set_half_carry(true);
}

void CPU::res_bit(Register8& reg, uint8_t bit_num) {
    uint8_t mask = ~(1 << bit_num);
    reg.set(reg.get() & mask);
}

void CPU::res_bit(uint8_t bit_num) {
    uint8_t mask = ~(1 << bit_num);
    mem->write(HL.get(), mem->read(HL.get()) & mask);
}

void CPU::set_bit(Register8& reg, uint8_t bit_num) {
    uint8_t mask = 1 << bit_num;
    reg.set(reg.get() | mask);
}

void CPU::set_bit(uint8_t bit_num) {
    uint8_t mask = 1 << bit_num;
    mem->write(HL.get(), mem->read(HL.get()) | mask);
}
