#include "cpu.h"

CPU::CPU() : AF(&A, &F), BC(&B, &C), DE(&D, &E), HL(&H, &L), PC(0x100), SP(0xFFFE) {}
