#pragma once

#include <iostream>
#include <cstdint>

namespace utils {
    std::ostream& hexify8(std::ostream& out);
    std::ostream& hexify16(std::ostream& out);

    constexpr unsigned KILOBYTE = 1024;
    constexpr unsigned SCREEN_X = 160;
    constexpr unsigned SCREEN_Y = 144;
}
