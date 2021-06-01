#include <iostream>

#include "cpu.h"
#include "memory.h"
#include "timer.h"
#include "interrupts.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [rom].gb" << std::endl;
    } else {       
        Interrupts* interrupts = new Interrupts();
        Timer* timer = new Timer(interrupts);
        Memory* mem = new MBC0(argv[1], interrupts, timer);
        
        bool debug = argc >= 3 && argv[2][0] == 'd';
        if (mem->is_loaded()) {
            CPU cpu = CPU(interrupts, timer, mem);
            cpu.main_loop(debug);

            delete interrupts;
            delete timer;
            delete mem;
        } else {
            std::cout << "Bad file name or error while reading file" << std::endl;
        }
    }
}
