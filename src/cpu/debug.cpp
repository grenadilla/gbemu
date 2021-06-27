#include "cpu.h"

#include <iostream>
#include "utils.h"

void CPU::print_debug(uint8_t opcode) {
    std::cout << opcode_table[opcode] << '\n'
        << "PC: " << utils::hexify16 << PC << '\n'
        << "SP: " << utils::hexify16 << SP << "\n\n"
        << "Registers: \n"
        << "AF: " << AF << '\n'
        << "BC: " << BC << '\n'
        << "DE: " << DE << '\n'
        << "HL: " << HL << "\n\n"
        << "Flags: \n"
        << "Zero: " << F.get_zero() << '\n' 
        << "Subtract: " << F.get_subtract() << '\n'
        << "Half Carry: " << F.get_half_carry() << '\n'
        << "Carry " << F.get_carry() << '\n' 
        << std::endl;
}

void CPU::print_line_debug(uint8_t opcode) {
    std::cout << utils::hexify16 << PC << ' ' << opcode_table[opcode] << "\n> ";
}

uint8_t CPU::get_opcode_debug() {
    return mem->read(PC, true);
}

uint16_t CPU::get_PC_debug() {
    return PC;
}

void CPU::print_imm_debug() {
    PC++;
    uint16_t imm = retrieve_imm16();
    PC -= 3;
    std::cout << utils::hexify16 << imm << " - " << std::dec << imm << '\n' << std::endl;
}

void CPU::print_mem_debug() {
    uint16_t data = mem->read(HL.get(), true);
    std::cout << utils::hexify8 << +data << " - " << std::dec << +data << '\n' << std::endl;
}