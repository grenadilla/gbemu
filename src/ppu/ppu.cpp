#include "ppu.h"

#include "utils.h"

PPU::PPU(Interrupts* interrupts) : interrupts(interrupts) { }

void PPU::set_renderer(SDL_Renderer* gb_renderer, SDL_Renderer* tile_data_renderer) {
    this->gb_renderer = gb_renderer;
    this->tile_data_renderer = tile_data_renderer;
}

PPU::Color PPU::fetch_tile_pixel(uint8_t* tile, int tile_offset_x, int tile_offset_y) {
    // Each line in the tile is 2 bytes
    uint8_t line_lsb = tile[tile_offset_y * 2];
    uint8_t line_msb = tile[tile_offset_y * 2 + 1];
    // Leftmost bit is leftmost pixel
    unsigned shift = utils::TILE_SIZE - 1 - tile_offset_x;
    uint8_t mask = 1 << shift;
    uint8_t lsb = (line_lsb & mask) >> shift;
    uint8_t msb = (line_msb & mask) >> shift;
    uint8_t palette_index = (msb << 1) | lsb;

    return bg_palette[palette_index];
}

PPU::Color PPU::get_bg_pixel(int pixel_x, int pixel_y) {
    int bg_pixel_x = (pixel_x - scroll_x) % utils::SCREEN_X;
    int bg_pixel_y = (pixel_y - scroll_y) % utils::SCREEN_Y;
    
    int tile_x = bg_pixel_x / utils::TILE_SIZE;
    int tile_y = bg_pixel_y / utils::TILE_SIZE;

    int tile_offset_x = bg_pixel_x % utils::TILE_SIZE;
    int tile_offset_y = bg_pixel_y % utils::TILE_SIZE;

    int tile_map_pointer = tile_y * NUM_TILES_X + tile_x;
    uint8_t tile_data_pointer = bg_map ? tile_map2[tile_map_pointer] : tile_map1[tile_map_pointer];
    uint8_t* tile;

    if (tile_data_area) {
        // Each tile is 16 bytes
        tile = tile_data + 16 * tile_data_pointer;
    } else {
        if (tile_data_pointer <= 127) {
            tile = tile_data + 0x1000 + tile_data_pointer;
        } else {
            tile = tile_data + 0x0800 + tile_data_pointer - 128;
        }
    }

    return fetch_tile_pixel(tile, tile_offset_x, tile_offset_y);
}

void PPU::set_draw_color(SDL_Renderer* renderer, Color color) {
    switch (color) {
        case WHITE:
            SDL_SetRenderDrawColor(renderer, 155, 188, 15, SDL_ALPHA_OPAQUE);
            break;
        case LIGHT_GREY:
            SDL_SetRenderDrawColor(renderer, 139, 172, 15, SDL_ALPHA_OPAQUE);
            break;
        case DARK_GREY:
            SDL_SetRenderDrawColor(renderer, 48, 98, 48, SDL_ALPHA_OPAQUE);
            break;
        case BLACK:
            SDL_SetRenderDrawColor(renderer, 15, 56, 15, SDL_ALPHA_OPAQUE);
            break;
    }
}

void PPU::draw_pixel(SDL_Renderer* renderer, int pixel_x, int pixel_y) {
    // TODO check for window and sprites
    Color pixel_color = get_bg_pixel(pixel_x, pixel_y);
    set_draw_color(renderer, pixel_color);

    SDL_Rect rect;
    rect.x = pixel_x * utils::SCREEN_MAGNIFY;
    rect.y = pixel_y * utils::SCREEN_MAGNIFY;
    rect.w = utils::SCREEN_MAGNIFY;
    rect.h = utils::SCREEN_MAGNIFY;

    SDL_RenderFillRect(renderer, &rect);
}

void PPU::draw_line(int pixel_y) {
    for (int pixel_x = 0; pixel_x < utils::SCREEN_X; pixel_x++) {
        draw_pixel(gb_renderer, pixel_x, pixel_y);
    }
}

void PPU::tick() {
    internal_timer--;
    switch (status) {
        case OAM_SEARCH: {
            if (internal_timer == 0) {
                status = READ;
                internal_timer = READ_LEN;
            }
            break;
        }

        case READ: {
            // For simplicity we draw the whole line in the middle of the read
            if (internal_timer == READ_LEN / 2) {
                draw_line(ly);
            } else if (internal_timer == 0) {
                status = HBLANK;
                internal_timer = HBLANK_LEN;

                if (stat_interrupt == HBLANK_STAT) {
                    interrupts->set_interrupt(Interrupts::LCD_STAT);
                }
            }
            break;
        }

        case HBLANK: {
            if (internal_timer == 0) {
                ly++;
                if (ly < 144) {
                    status = OAM_SEARCH;
                    internal_timer = OAM_SEARCH_LEN;

                    if (stat_interrupt == LYC_STAT || stat_interrupt == OAM_STAT) {
                        interrupts->set_interrupt(Interrupts::LCD_STAT);
                    }
                } else {
                    // Render each frame at start of VBLANK for speed
                    SDL_RenderPresent(gb_renderer);
                    status = VBLANK;
                    internal_timer = VBLANK_LEN;

                    interrupts->set_interrupt(Interrupts::VBLANK);
                    if (stat_interrupt == VBLANK_STAT) {
                        interrupts->set_interrupt(Interrupts::LCD_STAT);
                    }
                }
            }
            break;
        }

        case VBLANK: {
            if (internal_timer == 0) {
                //SDL_RenderPresent(gb_renderer);
                status = OAM_SEARCH;
                internal_timer = OAM_SEARCH_LEN;
                ly = 0;

                if (stat_interrupt == OAM_STAT) {
                    interrupts->set_interrupt(Interrupts::LCD_STAT);
                }
            } else if (internal_timer % LINE_LEN == 0){
                // Increment LY for each of the 10 VBLANK lines
                ly++;
            }
            break;
        }
    }
}

void PPU::run(unsigned cycles) {
    for (unsigned i = 0; i < cycles; i++) {
        tick();
    }
}

void PPU::draw_tile_display(uint16_t address, bool present) {
    if (tile_data_renderer) {
        // Each tile is 16 bytes
        int tile_display_x = (address / 16) % utils::TILE_DATA_WIDTH;
        int tile_display_y = (address / 16) / utils::TILE_DATA_WIDTH;
        int tile_offset_y = (address % 16) / 2;

        for (int tile_offset_x = 0; tile_offset_x < utils::TILE_SIZE; tile_offset_x++) {
            uint8_t* tile = tile_data + (address - (address % 16));
            Color pixel_color = fetch_tile_pixel(tile, tile_offset_x, tile_offset_y);
            set_draw_color(tile_data_renderer, pixel_color);
            SDL_Rect rect;
            rect.x = (tile_display_x * utils::TILE_SIZE + tile_offset_x) * utils::SCREEN_MAGNIFY + 1 + tile_display_x;
            rect.y = (tile_display_y * utils::TILE_SIZE + tile_offset_y) * utils::SCREEN_MAGNIFY + 1 + tile_display_y;
            rect.w = utils::SCREEN_MAGNIFY;
            rect.h = utils::SCREEN_MAGNIFY;

            SDL_RenderFillRect(tile_data_renderer, &rect);
        }

        if (present) {
            SDL_RenderPresent(tile_data_renderer);
        }
    }
}

void PPU::update_all_tile_display() {
    if (tile_data_renderer) {
        for (uint16_t address = 0; address < 6 * utils::KILOBYTE; address += 2) {
            draw_tile_display(address, false);
        }
        SDL_RenderPresent(tile_data_renderer);
    }
}