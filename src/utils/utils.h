#pragma once

#include <iostream>
#include <cstdint>

namespace utils {
    std::ostream& hexify8(std::ostream& out);
    std::ostream& hexify16(std::ostream& out);

    constexpr unsigned LIMIT_TICKS = 1000;

    constexpr unsigned KILOBYTE = 1024;
    constexpr unsigned SCREEN_X = 160;
    constexpr unsigned SCREEN_Y = 144;
    constexpr unsigned SCREEN_MAGNIFY = 4;

    // Each tile is 8 pixels
    constexpr unsigned TILE_SIZE = 8;

    constexpr unsigned TILE_DATA_WIDTH = 24;
    constexpr unsigned TILE_DATA_HEIGHT = 16;
    constexpr unsigned TILE_DATA_WINDOW_WIDTH = utils::TILE_SIZE * utils::SCREEN_MAGNIFY * utils::TILE_DATA_WIDTH + utils::TILE_DATA_WIDTH + 1;
    constexpr unsigned TILE_DATA_WINDOW_HEIGHT = utils::TILE_SIZE * utils::SCREEN_MAGNIFY * utils::TILE_DATA_HEIGHT + utils::TILE_DATA_HEIGHT + 1;
    constexpr unsigned BACKGROUND_SIZE = 256;

    // Each tile takes 8 x 8 tile takes up 16 bytes total,
    // with each line taking 2 bytes
    constexpr unsigned TILE_BYTE_SIZE = 16;
    constexpr unsigned TILE_LINE_BYTE_SIZE = 2;
    constexpr unsigned SPRITE_BYTE_SIZE = 4;

    // The screen coordinates of the top left corner of the Window are (WX-7,WY)
    constexpr unsigned WINDOW_X_OFFSET = 7;

    constexpr unsigned CLOCK_SPEED = 4194304;
    constexpr unsigned OAM_SIZE = 160;

    constexpr unsigned SPRITE_LIMIT = 10;

    constexpr uint16_t MBC_TYPE_ADDRESS = 0x0147;
    constexpr uint16_t MBC_ROM_SIZE_ADDRESS = 0x0148;
    constexpr uint16_t MBC_RAM_SIZE_ADDRESS = 0x0149;

    constexpr uint16_t TITLE_ADDRESS = 0x0134;

    constexpr unsigned AUDIO_FREQUENCY = 44100;
    constexpr unsigned AUDIO_BUFFER_SIZE = 2048;
    constexpr unsigned AUDIO_AMPLITUDE = 5000;
    constexpr unsigned AUDIO_CHANNEL_SAMPLE_SIZE = sizeof(float);
    constexpr unsigned AUDIO_SAMPLE_SIZE = AUDIO_CHANNEL_SAMPLE_SIZE * 2;

    constexpr unsigned MAX_VOLUME = 8;

    constexpr unsigned FRAME_SEQUENCER_PERIOD = 8192;

}
