#include "cpu.h"
#include "utils.h"
#include <iostream>
#include <sstream>
#include <iomanip>

CPU::CPU(Memory* mem) : AF(&A, &F), BC(&B, &C), DE(&D, &E), 
    HL(&H, &L), PC(0x100), SP(0xFFFE), mem(mem) {
    // From http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
    // registers are set to certain values
    AF.set(0x01B0);
    BC.set(0x0013);
    DE.set(0x00D8);
    HL.set(0x014D);
}

std::ostream& operator<<(std::ostream& out, const CPU::Opcode& op_data) {
    //return out << utils::hexify << op_data.opcode << ' ' << op_data.debug;
    return out << utils::hexify8 << +op_data.opcode << ' ' << op_data.debug;
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

void CPU::main_loop(bool debug) {
    std::string user_input;
    char action;
    unsigned num;

    while (true) {
        if (!debug) {
            tick();
            continue;
        }

        uint8_t opcode = mem->read(PC);
        std::cout << opcode_table[opcode] << std::endl;
        std::cout << "> ";
        std::getline(std::cin, user_input);
        std::istringstream iss(user_input);
        iss >> action >> num;

        if (action == 'c') {
            num = num == 0 ? 1 : num;
            for (unsigned i = 0; i < num; i++) {
                tick();
            }
        } else if (action == 'b') {
            while (opcode != mem->read(PC)) {
                tick();
            }
        } else if (action == 'd') {
            std::cout << opcode_table[opcode] << '\n'
                << "PC: " << utils::hexify16 << PC << '\n'
                << "SP: " << utils::hexify16 << SP << '\n'
                << "Registers: \n"
                << "AF: " << AF << '\n'
                << "BC: " << BC << '\n'
                << "DE: " << DE << '\n'
                << "HL: " << HL << '\n' << std::endl;
        } else if (action == 'q') {
            break;
        }
    }
}
