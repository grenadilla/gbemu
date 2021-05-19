#include "utils.h"
#include <iomanip>

namespace utils {
    std::ostream& hexify8(std::ostream& out) {
        out << "0x" << std::setfill('0') << std::setw(2) 
            << std::right << std::hex;
        return out;
    }

    std::ostream& hexify16(std::ostream& out) {
        out << "0x" << std::setfill('0') << std::setw(4) 
            << std::right << std::hex;
        return out;
    }
}
