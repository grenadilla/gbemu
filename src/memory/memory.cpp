#include "memory.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Memory::Memory(const std::string rom_path) : interrupt_flag(0xE0) {
    std::ifstream file(rom_path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        rom_data = std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), 
            std::istreambuf_iterator<char>());
    }
}

bool Memory::is_loaded() const {
    return !rom_data.empty();
}

uint8_t Memory::get_IE() const {
    return interrupt_enable;
}

uint8_t Memory::get_IF() const {
    return interrupt_flag;
}

void Memory::set_IE(uint8_t value) {
    interrupt_enable = value;
}

void Memory::set_IF(uint8_t value) {
    interrupt_flag = value;
}

uint8_t Memory::read(uint16_t address) const {
    /* --Memory Map--
    0000 	3FFF 	16KB ROM bank 00 	From cartridge, usually a fixed bank
    4000 	7FFF 	16KB ROM Bank 01~NN 	From cartridge, switchable bank via MBC (if any)
    8000 	9FFF 	8KB Video RAM (VRAM) 	Only bank 0 in Non-CGB mode. Switchable bank 0/1 in CGB mode
    A000 	BFFF 	8KB External RAM 	In cartridge, switchable bank if any
    C000 	CFFF 	4KB Work RAM (WRAM) bank 0 	
    D000 	DFFF 	4KB Work RAM (WRAM) bank 1~N 	Only bank 1 in Non-CGB mode. Switchable bank 1~7 in CGB mode
    E000 	FDFF 	Mirror of C000~DDFF (ECHO RAM) 	Typically not used
    FE00 	FE9F 	Sprite attribute table (OAM) 	
    FEA0 	FEFF 	Not Usable 	
    FF00 	FF7F 	I/O Registers 	
    FF80 	FFFE 	High RAM (HRAM) 	
    FFFF 	FFFF 	Interrupts Enable Register (IE) 	
    */
    if (address <= 0x3FFF) {
        // Cartridge fixed bank
        return rom_data[address];
    } else if (address <= 0x7FFF) {
        return rom_read(address);
    } else if (address <= 0x9FFF) {
        // VRAM
        return vram[address - 0x8000];
    } else if (address <= 0xBFFF) {
        // External RAM
        return ext_ram[address - 0xA000];
    } else if (address <= 0xCFFF) {
        // WRAM 0
        return wram0[address - 0xC000];
    } else if (address <= 0xDFFF) {
        // WRAM 1 or switchable bank for GBC
        return wram1[address - 0xD000];
    } else if (address <= 0xFDFF) {
        // Echo RAM for WRAM, usually not used
        if (address <= 0xEFFF) {
            return wram0[address - 0xE000];
        } else {
            return wram1[address - 0xF000];
        }
    } else if (address <= 0xFE9F) {
        // Sprite attribute table (OAM)
        return sprite_attr_table[address - 0xFE00];
    } else if (address <= 0xFEFF) {
        // Not usable
        std::cerr << "Attempted access to unusable memory at " << utils::hexify16 << address << std::endl;
        return 0;
    } else if (address <= 0xFF7F) {
        // TODO IO registers
        if (address == 0xFF0F) {
            // Interrupt Flag
            return interrupt_flag;
        } else if (address == 0xFFFF) {
            // Interrupt Enable
            return interrupt_enable; 
        } 
        return 0xFF;
    } else if (address <= 0xFFFE) {
        // High RAM
        return hram[address - 0xFF80];
    } else {
        return interrupt_enable;
    }
}

void Memory::write(uint16_t address, uint8_t value) {
    if (address <= 0x3FFF) {
        // Cartridge fixed bank
        std::cerr << "Invalid write into fixed bank ROM of " << utils::hexify8 << +value
            << " at memory address " << utils::hexify16 << address << std::endl;
    } else if (address <= 0x7FFF) {
        rom_write(address, value);
    } else if (address <= 0x9FFF) {
        // VRAM
        vram[address - 0x8000] = value;
    } else if (address <= 0xBFFF) {
        // External RAM
        ext_ram[address - 0xA000] = value;
    } else if (address <= 0xCFFF) {
        // WRAM 0
        wram0[address - 0xC000] = value;
    } else if (address <= 0xDFFF) {
        // WRAM 1 or switchable bank for GBC
        wram1[address - 0xD000] = value;
    } else if (address <= 0xFDFF) {
        // Echo RAM for WRAM, usually not used
        if (address <= 0xEFFF) {
            wram0[address - 0xE000] = value;
        } else {
            wram1[address - 0xF000] = value;
        }
    } else if (address <= 0xFE9F) {
        // Sprite attribute table (OAM)
        sprite_attr_table[address - 0xFE00] = value;
    } else if (address <= 0xFEFF) {
        // Not usable
        std::cerr << "Attempted write to unusable memory of " << utils::hexify8 << +value
            << " at memory address " << utils::hexify16 << address << std::endl;
    } else if (address <= 0xFF7F) {
        // TODO IO registers
        if (address == 0xFF01) {
            // Serial port
            std::cerr << (char) value;
        } else if (address == 0xFF0F) {
            // Interrupt Flag
            interrupt_flag = value;
        } else if (address == 0xFFFF) {
            // Interrupt Enable
            interrupt_enable = value;
        } 
    } else if (address <= 0xFFFE) {
        // High RAM
        hram[address - 0xFF80] = value;
    } else {
        interrupt_enable = value;
    }
}

MBC0::MBC0(const std::string rom_path) : Memory(rom_path) {}

uint8_t MBC0::rom_read(uint16_t address) const {
    return rom_data[address];
}

void MBC0::rom_write(uint16_t address, uint8_t value) {
    std::cerr << "Attempted write into ROM of " << utils::hexify8 << +value 
        << " at address " << utils::hexify16 << address << std::endl;
}