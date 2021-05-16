#include <iostream>
#include "cpu.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [rom].gb" << std::endl;
    } else {
        Memory* mem = new MBC0(argv[1]);
        bool debug = argc >= 3 && argv[2][0] == 'd';
        if (mem->is_loaded()) {
            CPU cpu = CPU(mem);
            cpu.main_loop(debug);
            delete mem;
        } else {
            std::cout << "Bad file name or error while reading file" << std::endl;
        }
    }
}
