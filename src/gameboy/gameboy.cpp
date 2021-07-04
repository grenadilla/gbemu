#include "gameboy.h"

#include <iostream>
#include <sstream>
#include <cstdint>

#include "utils.h"

Gameboy::Gameboy(std::string rom_path) : timer(&interrupts), ppu(&interrupts) {
    mem = new MBC0(rom_path, &interrupts, &timer, &ppu);
}

Gameboy::~Gameboy() {
    delete mem;
}

void Gameboy::run(bool debug) {
    if (!mem->is_loaded()) {
        std::cout << "Bad file name or error while reading file" << std::endl;
        return;
    }

    CPU cpu = CPU(&interrupts, mem);
    while (!quit) {
        if (!debug) {
            tick(cpu);
        } else {
            std::string user_input;
            char action;

            uint8_t opcode = cpu.get_opcode_debug();
            cpu.print_line_debug(opcode);
            std::getline(std::cin, user_input);
            std::istringstream iss(user_input);
            iss >> action;

            unsigned num = 1;

            switch (action) {
                case 'h': {
                    print_help();
                    break;
                }

                case 'c': {
                    iss >> num;
                    for (unsigned i = 0; i < num; i++) {
                        tick(cpu);
                    }
                    break;
                }

                case 'o': {
                    unsigned raw_op;
                    iss >> std::hex >> raw_op >> std::dec >> num;
                    uint8_t break_op = raw_op & 0xFF;

                    for (unsigned i = 0; i < num; i++) {
                        // tick once to go past breakpoint
                        tick(cpu);
                        while (break_op != cpu.get_opcode_debug()) {
                            tick(cpu);
                        }
                    }
                    break;
                }

                case 'b': {
                    uint16_t pc_break;
                    iss >> std::hex >> pc_break >> std::dec >> num;

                    for (unsigned i = 0; i < num; i++) {
                        // tick once to go past breakpoint
                        tick(cpu);
                        while (pc_break != cpu.get_PC_debug()) {
                            tick(cpu);
                        }
                    }
                    break;
                }

                case 'd': {
                    cpu.print_debug(opcode);
                    break;
                }

                case 'm': {
                    uint16_t address;
                    iss >> std::hex >> address;
                    uint16_t data = mem->read(address, true);
                    std::cout << utils::hexify8 << +data << " - " << std::dec << +data << '\n' << std::endl;
                    break;
                }

                case 'r': {
                    cpu.print_mem_debug();
                    break;
                }

                case 'i': {
                    cpu.print_imm_debug();
                    break;
                }

                case 't': {
                    timer.timer_debug(std::cout);
                    break;
                }

                case 'q': {
                    quit = true;
                    break;
                }

                default: {
                    std::cout << "Command not recognized. Use 'h' for help with a list of commands and their usage" << std::endl;
                }
            }
        }
    }
}

void Gameboy::tick(CPU& cpu) {
    // TODO graphics
    unsigned cycles = cpu.tick();
    timer.update_timers(cycles);
}

void Gameboy::print_help() {
    std::cout << "Command help:\n"
        << "c [num]              - Steps through [num] opcodes\n"
        << "o [hex opcode] [num] - Runs until the specified opcode is reached, optionally [num] times\n"
        << "b [PC value] [num]   - Runs until the program counter reaches the specified value, optionally [num] times\n"
        << "d                    - Debug information\n"
        << "m [hex address]      - Reads 8 bits from the specified address\n"
        << "r                    - Reads 8 bits from the address stored in HL\n"
        << "i                    - Reads 16 bit immediate after the program counter\n"
        << "t                    - Outputs timer debug information\n"
        << "q                    - Quit\n"
        << std::endl;
}