#include "cpu.h"

CPU::CPU() : AF(&A, &F), BC(&B, &C), DE(&D, &E), HL(&H, &L), PC(0x100), SP(0xFFFE) {
    // From http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
    // registers are set to certain values
    AF.set(0x01B0);
    BC.set(0x0013);
    DE.set(0x00D8);
    HL.set(0x014D);
}

uint8_t CPU::retrieve_imm8() {
    PC++;
    return RAM[PC];
}

uint16_t CPU::retrieve_imm16() {
    uint8_t lower = RAM[PC + 1];
    uint8_t upper = RAM[PC + 2];
    PC += 2;
    return static_cast<uint16_t>((upper << 8) | lower);
}

void CPU::push_stack(uint16_t val) {
    SP--;
    RAM[SP] = (val & 0xFF00) >> 8;
    SP--;
    RAM[SP] = val & 0x00FF;
}

uint16_t CPU::pop_stack() {
    uint8_t lower = RAM[SP];
    SP++;
    uint8_t upper = RAM[SP];
    SP++;
    return static_cast<uint16_t>((upper << 8) | lower);
}
