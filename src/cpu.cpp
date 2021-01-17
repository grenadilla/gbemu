#include "cpu.h"

CPU::CPU(Memory* mem) : AF(&A, &F), BC(&B, &C), DE(&D, &E), 
    HL(&H, &L), PC(0x100), SP(0xFFFE), mem(mem) {
    // From http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
    // registers are set to certain values
    AF.set(0x01B0);
    BC.set(0x0013);
    DE.set(0x00D8);
    HL.set(0x014D);
}

uint8_t CPU::retrieve_imm8() {
    uint8_t result = mem->read(PC);
    PC++;
    return result;
}

uint16_t CPU::retrieve_imm16() {
    uint8_t lower = mem->read(PC);
    uint8_t upper = mem->read(PC + 1);
    PC += 2;
    return static_cast<uint16_t>((upper << 8) | lower);
}

void CPU::push_stack(uint16_t val) {
    SP--;
    mem->write(SP, (val & 0xFF00) >> 8);
    SP--;
    mem->write(SP, val & 0x00FF);
}

uint16_t CPU::pop_stack() {
    uint8_t lower = mem->read(SP);
    SP++;
    uint8_t upper = mem->read(SP);
    SP++;
    return static_cast<uint16_t>((upper << 8) | lower);
}

void CPU::run_opcode() {
    uint16_t curr_PC = PC;
    uint8_t opcode = retrieve_imm8();
    Opcode op_data = opcode_table[opcode];
    unsigned cycles = jump_taken ? op_data.cycles : op_data.not_taken_cycles;
    jump_taken = false;
    // Call opcode function
    (this->*(op_data.func))();
}

void CPU::run_opcode_prefix() {
    uint8_t opcode = retrieve_imm8();
    Opcode op_data = opcode_prefixed_table[opcode];
    // The cycle length in the table include sthe CB prefix, so we subtract it
    unsigned cycles = op_data.cycles - 4;
    // Call opcode function
    (this->*(op_data.func))();
}

void CPU::tick() {
    // TODO take care of interrupts
    run_opcode();
}

void CPU::main_loop() {
    while (true) {
        tick();
    }
}
