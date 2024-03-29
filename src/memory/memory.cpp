#include "memory.h"

#include "mbc0.h"
#include "mbc1.h"
#include "mbc3.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <iomanip>

Memory* Memory::get_cartridge(const std::string& rom_path, Interrupts* interrupts, Timer* timer, APU* apu, PPU* ppu, Joypad* joypad) {
    std::ifstream file(rom_path, std::ios::in | std::ios::binary);
    if (file.is_open()) {
        const std::vector<uint8_t> rom_data = std::vector<uint8_t>((std::istreambuf_iterator<char>(file)), 
            std::istreambuf_iterator<char>());

        unsigned num_banks = 0;
        switch (rom_data[utils::MBC_ROM_SIZE_ADDRESS]) {
            case 0x00:
                num_banks = 0;
                break;
            case 0x01:
                num_banks = 4;
                break;
            case 0x02:
                num_banks = 8;
                break;
            case 0x03:
                num_banks = 16;
                break;
            case 0x04:
                num_banks = 32;
                break;
            case 0x05:
                num_banks = 64;
                break;
            case 0x06:
                num_banks = 128;
                break;
            case 0x07:
                num_banks = 256;
                break;
            case 0x08:
                num_banks = 512;
                break;
        }

        unsigned ram_size = 0;
        switch (rom_data[utils::MBC_RAM_SIZE_ADDRESS]) {
            case 0x00:
                ram_size = 0;
                break;
            case 0x01:
                ram_size = 2;
                break;
            case 0x02:
                ram_size = 8;
                break;
            case 0x03:
                ram_size = 32;
                break;
            case 0x04:
                ram_size = 128;
                break;
            case 0x05:
                ram_size = 64;
                break;
        }

        uint8_t mbc_type = rom_data[utils::MBC_TYPE_ADDRESS];
        switch (mbc_type) {
            case 0x00:
                std::cout << "MBC0" << std::endl;
                return new MBC0(rom_data, interrupts, timer, apu, ppu, joypad);
            case 0x01:
            case 0x02:
            case 0x03:
                std::cout << "MBC1" << std::endl;
                return new MBC1(rom_data, num_banks, ram_size, interrupts, timer, apu, ppu, joypad);
            case 0x0F:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
                std::cout << "MBC3" << std::endl;
                return new MBC3(rom_data, num_banks, ram_size, interrupts, timer, apu, ppu, joypad);
            default:
                return nullptr;
        }
    } else {
        return nullptr;
    }
}

Memory::Memory(const std::vector<uint8_t>& rom_data, Interrupts* interrupts, Timer* timer, APU* apu, PPU* ppu, Joypad* joypad) 
    : rom_data(rom_data), interrupts(interrupts), timer(timer), apu(apu), ppu(ppu), joypad(joypad) {
    char title_bytes[17] = {0};
    char* title_address = (char*) rom_data.data() + utils::TITLE_ADDRESS;
    for (size_t i = 0; i < utils::TITLE_LEN; i++) {
        title_bytes[i] = title_address[i];
        if (title_address[i] == 0) {
            break;
        }
    }
    title = std::string(title_bytes);
}

bool Memory::is_loaded() const {
    return !rom_data.empty();
}

uint8_t Memory::read(uint16_t address, bool transfer, bool debug) const {
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
    if (!transfer && OAM_countdown && !(address >= 0xFF80 && address < 0xFFFF)) {
        // In DMA OAM transfer, can only access HRMA
        std::cerr << "Attempted invalid non-HRAM read during DMA OAM transfer" << std::endl;
        return 0xFF;
    }

    if (address <= 0x3FFF) {
        // Cartridge fixed bank
        return mbc_read(address);
    } else if (address <= 0x7FFF) {
        return mbc_read(address);
    } else if (address <= 0x9FFF) {
        // VRAM
        if (address <= 0x97FF) {
            // Tile Data
            return ppu->read_tile_data(address - 0x8000, debug);
        } else if (address <= 0x9BFF) {
            return ppu->read_tile_map1(address - 0x9800, debug);
        } else {
            return ppu->read_tile_map2(address - 0x9C00, debug);
        }
    } else if (address <= 0xBFFF) {
        // External RAM
        return ram_read(address - 0xA000);
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
        return ppu->read_OAM(address - 0xFE00);
    } else if (address <= 0xFEFF) {
        // Not usable
        std::cerr << "Attempted access to unusable memory at " << utils::hexify16 << address << std::endl;
        return 0;
    } else if (address <= 0xFF7F) {
        return hardware_read(address);
    } else if (address <= 0xFFFE) {
        // High RAM
        return hram[address - 0xFF80];
    } else if (address == 0xFFFF) {
        return hardware_read(address);   
    } else {
        return 0xFF;
    }
}

void Memory::write(uint16_t address, uint8_t value) {
    if (OAM_countdown && !(address >= 0xFF80 && address < 0xFFFF)) {
        // In DMA OAM transfer, can only access HRMA
        std::cerr << "Attempted invalid non-HRAM write during DMA OAM transfer" << std::endl;
        return;
    }

    if (address <= 0x3FFF) {
        // Cartridge fixed bank
        mbc_write(address, value);
    } else if (address <= 0x7FFF) {
        mbc_write(address, value);
    } else if (address <= 0x9FFF) {
        // VRAM
        if (address <= 0x97FF) {
            // Tile Data
            ppu->write_tile_data(address - 0x8000, value);
        } else if (address <= 0x9BFF) {
            ppu->write_tile_map1(address - 0x9800, value);
        } else {
            ppu->write_tile_map2(address - 0x9C00, value);
        }
    } else if (address <= 0xBFFF) {
        // External RAM
        ram_write(address - 0xA000, value);
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
        ppu->write_OAM(address - 0xFE00, value);
    } else if (address <= 0xFEFF) {
        // Not usable
        std::cerr << "Attempted write to unusable memory of " << utils::hexify8 << +value
            << " at memory address " << utils::hexify16 << address << std::endl;
    } else if (address <= 0xFF7F) {
        hardware_write(address, value);
    } else if (address <= 0xFFFE) {
        // High RAM
        hram[address - 0xFF80] = value;
    } else if (address == 0xFFFF) {
        hardware_write(address, value);
    }
}

void Memory::tick(unsigned cycles) {
    if (OAM_countdown > utils::OAM_SIZE) {
        // Delay
        OAM_countdown--;
    } else if (OAM_countdown) {
        unsigned m_cycles = cycles / 4;
        unsigned start = utils::OAM_SIZE - OAM_countdown;
        unsigned end = start + m_cycles < utils::OAM_SIZE ? start + m_cycles : utils::OAM_SIZE;
        for (unsigned index = start; index < end; index++) {
            uint8_t value = read(OAM_base + index, true, false);
            ppu->write_OAM(index, value);
            OAM_countdown--;
        }
    }
}