#pragma once

#include <iostream>
#include <cstdint>

namespace utils {
    std::ostream& hexify8(std::ostream& out);
    std::ostream& hexify16(std::ostream& out);

    constexpr unsigned LIMIT_TICKS = 5000;

    constexpr unsigned KILOBYTE = 1024;
    constexpr unsigned SCREEN_X = 160;
    constexpr unsigned SCREEN_Y = 144;
    constexpr unsigned SCREEN_MAGNIFY = 4;
    constexpr static unsigned TILE_SIZE = 8;
    constexpr unsigned TILE_DATA_WIDTH = 24;
    constexpr unsigned TILE_DATA_HEIGHT = 16;
    constexpr unsigned TILE_DATA_WINDOW_WIDTH = utils::TILE_SIZE * utils::SCREEN_MAGNIFY * utils::TILE_DATA_WIDTH + utils::TILE_DATA_WIDTH + 1;
    constexpr unsigned TILE_DATA_WINDOW_HEIGHT = utils::TILE_SIZE * utils::SCREEN_MAGNIFY * utils::TILE_DATA_HEIGHT + utils::TILE_DATA_HEIGHT + 1;

    constexpr unsigned CLOCK_SPEED = 4194304;
    constexpr unsigned CLOCK_SPEED_MILLI = CLOCK_SPEED * 1000;
}
