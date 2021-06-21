#include "cpu.h"

#include "utils.h"

#include <iostream>
#include <sstream>
#include <iomanip>

CPU::CPU(Interrupts* interrupts, Memory* mem) : AF(&A, &F), BC(&B, &C), DE(&D, &E), 
    HL(&H, &L), interrupts(interrupts), mem(mem) {
    // From http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
    // registers are set to certain values
    AF.set(0x01B0);
    BC.set(0x0013);
    DE.set(0x00D8);
    HL.set(0x014D);
}

std::ostream& operator<<(std::ostream& out, const CPU::Opcode& op_data) {
    return out << utils::hexify8 << +(op_data.opcode) << ' ' << op_data.debug;
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

unsigned CPU::run_opcode() {
    uint16_t curr_PC = PC;
    uint8_t opcode = retrieve_imm8();

    // See HALT bug, PC not incremented
    if (halt_bug) {
        PC--;
        halt_bug = false;
    }

    Opcode op_data = opcode_table[opcode];
    unsigned cycles;

    // Call opcode function
    if (opcode == 0xCB) {
        opcode = retrieve_imm8();
        op_data = opcode_prefixed_table[opcode];
    }

    (this->*(op_data.func))();
    
    cycles = jump_taken ? op_data.cycles : op_data.not_taken_cycles;
    jump_taken = false;
    return cycles;
}

unsigned CPU::tick() {
    unsigned cycles = 0;

    // Clear HALT if an interrupt is received
    if (interrupts->get_IE() & interrupts->get_IF() & 0x1F) {
        halted = false;
    }

    uint8_t interrupt_address = interrupts->get_interrupt();
    if (interrupt_address) {
        push_stack(PC);
        PC = interrupt_address;
        cycles += 20;
    }

    if (!halted) {
        cycles += run_opcode();
    } else {
        cycles += 4;
    }

    return cycles;
}
