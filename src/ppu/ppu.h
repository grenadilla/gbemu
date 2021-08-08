#pragma once

#include "utils.h"
#include "interrupts.h"

#include <cstdint>
#include <SDL2/SDL.h>

constexpr int KILOBYTE = 1024;

class PPU {
    public:
        PPU(Interrupts* interrupts);
        void set_renderer(SDL_Renderer* gb_renderer, SDL_Renderer* tile_data_renderer);

        void write_tile_data(uint16_t address, uint8_t value);
        void write_tile_map1(uint16_t address, uint8_t value);
        void write_tile_map2(uint16_t address, uint8_t value);

        uint8_t read_tile_data(uint16_t address, bool debug = false);
        uint8_t read_tile_map1(uint16_t address, bool debug = false);
        uint8_t read_tile_map2(uint16_t address, bool debug = false);

        void write_lcd_control(uint8_t value);
        uint8_t read_lcd_control();

        void set_scroll_y(uint8_t value);
        void set_scroll_x(uint8_t value);
        void set_lyc(uint8_t value);
        void set_window_y(uint8_t value);
        void set_window_x(uint8_t value);

        uint8_t get_scroll_y();
        uint8_t get_scroll_x();
        uint8_t get_ly();
        uint8_t get_lyc();
        uint8_t get_window_y();
        uint8_t get_window_x();

        void write_stat(uint8_t value);
        uint8_t read_stat();

        void write_palette(uint8_t value);
        uint8_t read_palette();

        void write_obj_palette0(uint8_t value);
        uint8_t read_obj_palette0();

        void write_obj_palette1(uint8_t value);
        uint8_t read_obj_palette1();

        void write_OAM(uint16_t address, uint8_t value);
        uint8_t read_OAM(uint16_t address);

        void run(unsigned cycles);

    private:
        enum Mode {
            OAM_SEARCH = 2,
            READ = 3,
            HBLANK = 0,
            VBLANK = 1,
        };

        enum Interrupt_Source {
            LYC_STAT = 0x40,
            OAM_STAT = 0x20,
            VBLANK_STAT = 0x10,
            HBLANK_STAT = 0x08,
        };

        enum Color {
            WHITE = 0,
            LIGHT_GREY = 1,
            DARK_GREY = 2,
            BLACK = 3,

            // Only used internally for implementation, will never be actually rendered
            TRANSPARENT = 4
        };

        constexpr static unsigned NUM_TILES_X = 32;
        constexpr static unsigned NUM_TILES_Y = 32;
        constexpr static unsigned OAM_SEARCH_LEN = 80;
        constexpr static unsigned READ_LEN = 172;
        constexpr static unsigned HBLANK_LEN = 204;
        constexpr static unsigned LINE_LEN = OAM_SEARCH_LEN + READ_LEN + HBLANK_LEN;
        constexpr static unsigned VBLANK_LEN = 10 * LINE_LEN;

        // TODO set color data to map to rgb
        // constexpr COLORS[4] = {...}

        uint8_t tile_data[6 * utils::KILOBYTE];
        uint8_t tile_map1[utils::KILOBYTE];
        uint8_t tile_map2[utils::KILOBYTE];
        uint8_t OAM[utils::OAM_SIZE] = {0};

        // LCD control
        bool lcd_enable = true;
        bool window_map = false; // false - 0x9800-0x9BFF, true - 0x9C00 - 0x9FFF
        bool window_enable = false;
        bool tile_data_area = false; // false - 0x8800-0x9700, true 0x8000-0x8FFF
        bool bg_map = false; // false - 0x9800-0x9BFF, true - 0x9C00 - 0x9FFF
        bool obj_size = false; // false - 8x8, true - 8x16
        bool obj_enable = false;
        bool bg_window_enable = true;

        uint8_t scroll_y = 0;
        uint8_t scroll_x = 0;
        uint8_t ly = 0;
        uint8_t lyc = 0;
        uint8_t window_y = 0;
        uint8_t window_x = 0;

        Interrupt_Source stat_interrupt = LYC_STAT;
        Mode status = OAM_SEARCH;
        Color bg_palette[4] = {WHITE, BLACK, BLACK, BLACK};
        Color obj_palette0[4] = {TRANSPARENT, BLACK, BLACK, BLACK};
        Color obj_palette1[4] = {TRANSPARENT, BLACK, BLACK, BLACK};

        unsigned internal_timer = OAM_SEARCH_LEN;

        Interrupts* interrupts;
        SDL_Renderer* gb_renderer = nullptr;
        SDL_Renderer* tile_data_renderer = nullptr;

        bool validate_vram_access(std::string source = "[UNKNOWN SOURCE]");

        /* TODO switch over to emulating pixel FIFO
         * For now we go pixel by pixel instead of tile by tile
         * Use timings 80 - 172 - 204
         */
        Color fetch_tile_pixel(uint8_t* tile, int tile_offset_x, int tile_offset_y, Color* palette, bool hide_obj = false);
        uint8_t* get_bg_tile(int tile_map_pointer);

        void draw_pixel(SDL_Renderer* renderer, int pixel_x, int pixel_y);
        void draw_line(int pixel_y);
        void draw_tile_display(uint16_t address, bool present = true);
        void update_all_tile_display();
        void set_draw_color(SDL_Renderer* renderer, Color color);
        void tick();
};