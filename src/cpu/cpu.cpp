#include "cpu.h"

#include "utils.h"

#include <iostream>
#include <sstream>
#include <iomanip>

CPU::CPU(Interrupts* interrupts, Timer* timer, Memory* mem) : AF(&A, &F), BC(&B, &C), DE(&D, &E), 
    HL(&H, &L), interrupts(interrupts), mem(mem), timer(timer) {
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

void CPU::tick() {
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

    timer->update_timers(cycles);
}

void CPU::main_loop(bool debug) {
    if (debug) {
        main_loop_debug();
    } else {
        while (true) {
            tick();
        }
    }
}

void CPU::main_loop_debug() {
    std::string user_input;
    char action;

    while (true) {
        uint8_t opcode = mem->read(PC);
        std::cout << utils::hexify16 << PC << ' ' << opcode_table[opcode] << "\n> ";
        std::getline(std::cin, user_input);
        std::istringstream iss(user_input);
        iss >> action;
        
        if (action == 'h') {
            std::cout << "Command help:\n"
                << "c [num]              - Steps through [num] opcodes\n"
                << "o [hex opcode] [num] - Runs until the specified opcode is reached, optionally [num] times\n"
                << "b [PC value] [num]   - Runs until the program counter reaches the specified value, optionally [num] times\n"
                << "d                    - Debug information\n"
                << "m [hex address]      - Reads 8 bits from the specified address\n"
                << "r                    - Reads 8 bits from the address stored in HL\n"
                << "i                    - Reads 8 bit immediate after the program counter\n"
                << "t                    - Outputs timer debug information\n"
                << "q                    - Quit\n"
                << std::endl;
        } else if (action == 'c') {
            unsigned num = 1;
            iss >> num;
            for (unsigned i = 0; i < num; i++) {
                tick();
            }
        } else if (action == 'o') {
            unsigned raw_op;
            unsigned num = 1;
            iss >> std::hex >> raw_op >> std::dec >> num;
            uint8_t break_op = raw_op & 0xFF;

            for (unsigned i = 0; i < num; i++) {
                // tick once to go past breakpoint
                tick();
                while (break_op != mem->read(PC)) {
                    tick();
                }
            }
        } else if (action == 'b') {
            uint16_t pc_break;
            unsigned num = 1;
            iss >> std::hex >> pc_break >> std::dec >> num;

            for (unsigned i = 0; i < num; i++) {
                // tick once to go past breakpoint
                tick();
                while (pc_break != PC) {
                    tick();
                }
            }
        } else if (action == 'd') {
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
        } else if (action == 'm') {
            uint16_t address;
            iss >> std::hex >> address;
            uint16_t data = mem->read(address);
            std::cout << utils::hexify8 << +data << " - " << std::dec << +data << '\n' << std::endl;
        } else if (action == 'r') {
            uint16_t data = mem->read(HL.get());
            std::cout << utils::hexify8 << +data << " - " << std::dec << +data << '\n' << std::endl;
        } else if (action == 'i') {
            uint8_t imm = mem->read(PC + 1);
            std::cout << utils::hexify8 << +imm << " - " << std::dec << +imm << '\n' << std::endl;
        } else if (action == 't') {
            timer->timer_debug(std::cout);
        } else if (action == 'q') {
            break;
        }
    }
}
