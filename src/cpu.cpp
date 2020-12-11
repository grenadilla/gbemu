#include "cpu.h"

CPU::CPU() : AF(&A, &F), BC(&B, &C), DE(&D, &E), HL(&H, &L), PC(0x100), SP(0xFFFE) {
    // From http://www.codeslinger.co.uk/pages/projects/gameboy/hardware.html
    // registers are set to certain values
    AF.set(0x01B0);
    BC.set(0x0013);
    DE.set(0x00D8);
    HL.set(0x014D);
}
