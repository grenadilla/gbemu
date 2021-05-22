#pragma once

#include <iostream>
#include <cstdint>

namespace utils {
    constexpr unsigned CLOCK_SPEED = 4194304;
    constexpr unsigned DIV_TIMER_SPEED = 16384;
    constexpr unsigned TIMER_SPEEDS[] = {4096, 262144, 65536, 16384};
    constexpr unsigned TIMER_THRESHOLDS[] = {1024, 16, 64, 256};
    constexpr unsigned DIV_TIMER_THRESHOLD = CLOCK_SPEED / DIV_TIMER_SPEED;

    std::ostream& hexify8(std::ostream& out);
    std::ostream& hexify16(std::ostream& out);
}
