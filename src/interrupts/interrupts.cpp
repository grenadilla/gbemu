#include "interrupts.h"

#include <iostream>

uint8_t Interrupts::get_IF() const {
    return interrupt_flags;
}

void Interrupts::set_IF(uint8_t value) {
    interrupt_flags = value;
}

uint8_t Interrupts::get_IE() const {
    return interrupt_enable;
}

void Interrupts::set_IE(uint8_t value) {
    interrupt_enable = value;
}

void Interrupts::enable_interrupts() {
    ime_delay = true;
}

void Interrupts::disable_interrupts() {
    ime_delay = false;
    ime = false;
}

void Interrupts::set_interrupt(uint8_t flag) {
    interrupt_flags |= flag;
}

bool Interrupts::get_IME() const {
    return ime;
}

/* INTERRUPT EXECUTION
 * https://gbdev.gg8.se/wiki/articles/Interrupts
 * IME is set to false to prevent other interrupts
 * Corresponding bit in IF is reset
 * 2 NOPS occur (machine cycles where nothing happens)
 * PC is pushed to stack (2 cycles)
 * High byte of PC set to zero, low byte set to handler address (1 cycle)
 * Total 5 cycles (20 T-cycles)
 * Handler addresses: $40,$48,$50,$58,$60
 * v-blank, lcd-stat, timer, serial, joypad
 */
// Returns address of interrupt vector
uint8_t Interrupts::get_interrupt() {
    uint8_t result = 0;
    if (ime) {
        // Check interrupts
        uint8_t interrupts = interrupt_enable & interrupt_flags & 0x1F;
        for (uint8_t i = 0; i < 5; i++) {
            uint8_t mask = 0x01 << i;
            if (interrupts & mask) {
                // Reset interrupt
                interrupt_flags &= ~mask;
                ime = false;
                result = (i * 0x08) + 0x40;
            }
        }
    }

    // TODO see how EI interacts with interrupts right after
    if (ime_delay) {
        ime = true;
        ime_delay = false;
    }

    return result;
}

void Interrupts::print_debug() {
    std::cout << "Interrupt Master Enable: " << (int) ime << std::endl;

    if (interrupt_enable & VBLANK) {
        std::cout << "VBLANK enabled" << std::endl;
    }
    if (interrupt_enable & LCD_STAT) {
        std::cout << "STAT enabled" << std::endl;
    }
    if (interrupt_enable & TIMER) {
        std::cout << "TIMER enabled" << std::endl;
    }
    if (interrupt_enable & SERIAL) {
        std::cout << "SERIAL enabled" << std::endl;
    }
    if (interrupt_enable & JOYPAD) {
        std::cout << "JOYPAD enabled" << std::endl;
    }

    std::cout << std::endl;
}