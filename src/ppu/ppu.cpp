#include "ppu.h"

#include "utils.h"

PPU::PPU(Interrupts* interrupts) : interrupts(interrupts) { }

void PPU::set_renderer(SDL_Renderer* gb_renderer, SDL_Renderer* tile_data_renderer) {
    this->gb_renderer = gb_renderer;
    this->tile_data_renderer = tile_data_renderer;
}

PPU::Color PPU::fetch_tile_pixel(uint8_t* tile, int tile_offset_x, int tile_offset_y, Color* palette, bool hide_obj) {
    // Each line in the tile is 2 bytes
    uint8_t line_lsb = tile[tile_offset_y * utils::TILE_LINE_BYTE_SIZE];
    uint8_t line_msb = tile[tile_offset_y * utils::TILE_LINE_BYTE_SIZE + 1];
    // Leftmost bit is leftmost pixel
    unsigned shift = utils::TILE_SIZE - (tile_offset_x + 1);
    uint8_t mask = 1 << shift;
    uint8_t lsb = (line_lsb & mask) >> shift;
    uint8_t msb = (line_msb & mask) >> shift;
    uint8_t palette_index = (msb << 1) | lsb;

    // Used for bg and window over obj flag for sprites
    if (hide_obj && palette_index == 0) {
        return TRANSPARENT;
    }

    return palette[palette_index];
}

uint8_t* PPU::get_bg_win_tile(int tile_map_pointer, bool tilemap) {
    uint8_t tile_data_pointer = tilemap ? tile_map2[tile_map_pointer] : tile_map1[tile_map_pointer];
    uint8_t* tile;

    // Multiply by 16 when addressing as each tile is 16 bytes
    if (tile_data_area) {
        tile = tile_data + utils::TILE_BYTE_SIZE * tile_data_pointer;
    } else {
        if (tile_data_pointer <= 127) {
            tile = tile_data + 0x1000 + utils::TILE_BYTE_SIZE * tile_data_pointer;
        } else {
            // Subtract 128 to simulate converting unsigned tile data pointer to become signed
            tile = tile_data + 0x0800 + utils::TILE_BYTE_SIZE * (tile_data_pointer - 128);
        }
    }

    return tile;
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
        default:
            std::cerr << "Invalid color: " << (int) color << std::endl;
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    }
}

void PPU::draw_pixel(SDL_Renderer* renderer, int pixel_x, int pixel_y, std::set<uint8_t*>& drawn_sprites) {
    Color pixel_color = TRANSPARENT;
    bool bg_window_over = false;

    if (obj_enable) {
        // Check sprites
        uint8_t lowest_x = 0xFF;
        uint8_t* selected_sprite = nullptr;
        for (uint8_t* sprite_attr = OAM; sprite_attr < OAM + utils::OAM_SIZE; sprite_attr += utils::SPRITE_BYTE_SIZE) {
            if (drawn_sprites.size() == utils::SPRITE_LIMIT && drawn_sprites.count(sprite_attr) == 0) {
                continue;
            }

            // Each sprite attribute is 4 bytes
            // Sprite y is by bottom of sprite
            uint8_t sprite_y = sprite_attr[0];
            uint8_t sprite_x = sprite_attr[1];
            uint8_t tile_index = sprite_attr[2];
            uint8_t sprite_flags = sprite_attr[3];

            bool y_flip = sprite_flags & 0x40;
            bool x_flip = sprite_flags & 0x20;
            bool palette_number = sprite_flags & 0x10;

            // Priority is determined by which sprite has the lower x value
            // and which sprite is first in OAM for tiebreakers
            if (sprite_x >= lowest_x) {
                continue;
            }

            uint8_t* tile = nullptr;
            int tile_offset_x;
            int tile_offset_y;

            // Remember tiles are 16 bytes
            // When 8 x 16 tiles, ignore LSB of tile index, enforced by hardware
            // When y is flipped for 8 x 16 sprites, we have to worry about flipping which object we are using too
            if (obj_size && pixel_y < sprite_y && (pixel_y + utils::TILE_SIZE) >= sprite_y && (pixel_x + utils::TILE_SIZE) >= sprite_x && pixel_x < sprite_x) {
                // Bottom tile of 8 x 16 sprite
                if (y_flip) {
                    tile = tile_data + (tile_index & (obj_size ? 0xFE : 0xFF)) * utils::TILE_BYTE_SIZE;
                } else {
                    tile = tile_data + (tile_index | 0x01) * utils::TILE_BYTE_SIZE;
                }
                tile_offset_x = pixel_x - sprite_x + utils::TILE_SIZE;
                tile_offset_y = pixel_y - sprite_y + utils::TILE_SIZE;
            } else if ((pixel_y + utils::TILE_SIZE) < sprite_y && (pixel_y + 2 * utils::TILE_SIZE) >= sprite_y && (pixel_x + utils::TILE_SIZE) >= sprite_x && pixel_x < sprite_x) {
                // Top tile of 8 x 16 sprite or in 8 x 8 sprite
                if (y_flip && obj_size) {
                    tile = tile_data + (tile_index | 0x01) * utils::TILE_BYTE_SIZE;
                } else {
                    tile = tile_data + (tile_index & (obj_size ? 0xFE : 0xFF)) * utils::TILE_BYTE_SIZE;
                }
                tile_offset_x = pixel_x - sprite_x + utils::TILE_SIZE;
                tile_offset_y = pixel_y - sprite_y + 2 * utils::TILE_SIZE;
            } else {
                continue;
            }

            if (y_flip) {
                tile_offset_y = utils::TILE_SIZE - (tile_offset_y + 1);
            }
            if (x_flip) {
                tile_offset_x = utils::TILE_SIZE - (tile_offset_x + 1);
            }

            Color sprite_color = fetch_tile_pixel(tile, tile_offset_x, tile_offset_y, palette_number ? obj_palette1 : obj_palette0);
            if (sprite_color != TRANSPARENT) {
                pixel_color = sprite_color;
                bg_window_over = sprite_flags & 0x80;
                lowest_x = sprite_x;
                selected_sprite = sprite_attr;
            }
        }

        if (selected_sprite != nullptr) {
            drawn_sprites.insert(selected_sprite);
        }
    }

    if ((bg_window_over || pixel_color == TRANSPARENT) && bg_window_enable && window_enable) {
        int win_pixel_x = (pixel_x - window_x + utils::WINDOW_X_OFFSET);
        int win_pixel_y = (window_internal_line_counter - window_y);

        // Check if window in bounds
        if (win_pixel_x >= 0 && win_pixel_x < utils::SCREEN_X && win_pixel_y >= 0 && win_pixel_y < utils::SCREEN_Y) {
            int tile_x = win_pixel_x / utils::TILE_SIZE;
            int tile_y = win_pixel_y / utils::TILE_SIZE;

            int tile_offset_x = win_pixel_x % utils::TILE_SIZE;
            int tile_offset_y = win_pixel_y % utils::TILE_SIZE;

            int tile_map_pointer = tile_y * NUM_TILES_X + tile_x;
            uint8_t* tile = get_bg_win_tile(tile_map_pointer, window_map);

            // Note the only time bg_color will be TRANSPARENT will be when there is a non-transparent
            // sprite underneath with bg_window_over set to true
            Color win_color = fetch_tile_pixel(tile, tile_offset_x, tile_offset_y, bg_palette, bg_window_over);
            if (win_color != TRANSPARENT) {
                pixel_color = win_color;
            }
        }
    }

    if ((bg_window_over || pixel_color == TRANSPARENT) && bg_window_enable) {
        // Check background
        int bg_pixel_x = (pixel_x + scroll_x) % utils::BACKGROUND_SIZE;
        int bg_pixel_y = (pixel_y + scroll_y) % utils::BACKGROUND_SIZE;
        
        int tile_x = bg_pixel_x / utils::TILE_SIZE;
        int tile_y = bg_pixel_y / utils::TILE_SIZE;

        int tile_offset_x = bg_pixel_x % utils::TILE_SIZE;
        int tile_offset_y = bg_pixel_y % utils::TILE_SIZE;

        int tile_map_pointer = tile_y * NUM_TILES_X + tile_x;
        uint8_t* tile = get_bg_win_tile(tile_map_pointer, bg_map);

        // Note the only time bg_color will be TRANSPARENT will be when there is a non-transparent
        // sprite underneath with bg_window_over set to true
        Color bg_color = fetch_tile_pixel(tile, tile_offset_x, tile_offset_y, bg_palette, bg_window_over);
        if (bg_color != TRANSPARENT) {
            pixel_color = bg_color;
        }
    }

    if (pixel_color == TRANSPARENT && !bg_window_enable) {
        pixel_color = bg_palette[0];
    }

    set_draw_color(renderer, pixel_color);

    SDL_Rect rect;
    rect.x = pixel_x * utils::SCREEN_MAGNIFY;
    rect.y = pixel_y * utils::SCREEN_MAGNIFY;
    rect.w = utils::SCREEN_MAGNIFY;
    rect.h = utils::SCREEN_MAGNIFY;

    SDL_RenderFillRect(renderer, &rect);
}

void PPU::draw_line(int pixel_y) {
    std::set<uint8_t*> drawn_sprites;
    for (int pixel_x = 0; pixel_x < utils::SCREEN_X; pixel_x++) {
        draw_pixel(gb_renderer, pixel_x, pixel_y, drawn_sprites);
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
                if (gb_renderer != nullptr) {
                    // Renderer can be nullptr if ran without graphics
                    draw_line(ly);
                }
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
                increment_line();
                if (stat_interrupt == LYC_STAT && ly == lyc) {
                    interrupts->set_interrupt(Interrupts::LCD_STAT);
                }
                if (ly < utils::SCREEN_Y) {
                    status = OAM_SEARCH;
                    internal_timer = OAM_SEARCH_LEN;

                    if (stat_interrupt == OAM_STAT) {
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
                window_internal_line_counter = 0;

                if (stat_interrupt == OAM_STAT) {
                    interrupts->set_interrupt(Interrupts::LCD_STAT);
                }
            } else if (internal_timer % LINE_LEN == 0){
                // Increment LY for each of the 10 VBLANK lines
                increment_line();
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
        int tile_display_x = (address / utils::TILE_BYTE_SIZE) % utils::TILE_DATA_WIDTH;
        int tile_display_y = (address / utils::TILE_BYTE_SIZE) / utils::TILE_DATA_WIDTH;
        int tile_offset_y = (address % utils::TILE_BYTE_SIZE) / utils::TILE_LINE_BYTE_SIZE;

        for (int tile_offset_x = 0; tile_offset_x < utils::TILE_SIZE; tile_offset_x++) {
            uint8_t* tile = tile_data + (address - (address % utils::TILE_BYTE_SIZE));
            Color pixel_color = fetch_tile_pixel(tile, tile_offset_x, tile_offset_y, bg_palette);
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
        for (uint16_t address = 0; address < 6 * utils::KILOBYTE; address += utils::TILE_LINE_BYTE_SIZE) {
            draw_tile_display(address, false);
        }
        SDL_RenderPresent(tile_data_renderer);
    }
}

void PPU::increment_line() {
    ly++;
    // Only increment window internal line counter if window is visible
    if (window_x >= 0 && window_x < utils::SCREEN_X && window_y >= 0 && window_y < utils::SCREEN_Y) {
        window_internal_line_counter++;
    }
}