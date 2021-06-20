#include <iostream>

#include "gameboy.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [rom].gb" << std::endl;
    } else {       
        bool debug = argc >= 3 && argv[2][0] == 'd';
        Gameboy gb(argv[1]);
        gb.run(debug);
    }
}
