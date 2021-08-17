#include "gameboy.h"

#include <iostream>
#include <sstream>
#include <cstdint>

#include "utils.h"

Gameboy::Gameboy(std::string rom_path) : timer(&interrupts), ppu(&interrupts), joypad(&interrupts) {
    mem = Memory::get_cartridge(rom_path, &interrupts, &timer, &ppu, &joypad);
    tick_countdown = utils::LIMIT_TICKS;
}

Gameboy::~Gameboy() {
    delete mem;
}

void Gameboy::init_graphics(bool tilemap) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize SDL! SDL Error: " << SDL_GetError() << std::endl;
        quit = true;
        return;
    }

    // Set up main gameboy screen
    window = SDL_CreateWindow
    (
        "Gameboy Emulator", 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        utils::SCREEN_X * utils::SCREEN_MAGNIFY,
        utils::SCREEN_Y * utils::SCREEN_MAGNIFY,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP
    );

    if (window == nullptr) {
        std::cerr << "SDL window could not be created! SDL Error: " << SDL_GetError() << std::endl;
    }

    // TODO add option to select renderer type
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == nullptr) {
        std::cerr << "SDL renderer could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Set up debug tile data screen
    if (tilemap) {
        tile_window = SDL_CreateWindow
        (
            "Gameboy Emulator Tile Data", 
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            utils::TILE_DATA_WINDOW_WIDTH,
            utils::TILE_DATA_WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP
        );

        if (tile_window == nullptr) {
            std::cerr << "SDL window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        }

        tile_renderer = SDL_CreateRenderer(tile_window, -1, SDL_RENDERER_SOFTWARE);
        if (tile_renderer == nullptr) {
            std::cerr << "SDL renderer could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        }

        SDL_SetRenderDrawColor(tile_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(tile_renderer);

        // Draw grid
        SDL_SetRenderDrawColor(tile_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        for (int x = 0; x <= utils::TILE_DATA_WIDTH; x++) {
            SDL_RenderDrawLine(tile_renderer, 
                x + x * utils::TILE_SIZE * utils::SCREEN_MAGNIFY,
                0, 
                x + x * utils::TILE_SIZE * utils::SCREEN_MAGNIFY,
                utils::TILE_DATA_WINDOW_HEIGHT - 1
            );
        }
        for (int y = 0; y <= utils::TILE_DATA_HEIGHT; y++) {
            SDL_RenderDrawLine(tile_renderer,
                0,
                y + y * utils::TILE_SIZE * utils::SCREEN_MAGNIFY,
                utils::TILE_DATA_WINDOW_WIDTH - 1,
                y + y * utils::TILE_SIZE * utils::SCREEN_MAGNIFY
            );
        }

        SDL_RenderPresent(tile_renderer);
    }

    ppu.set_renderer(renderer, tile_renderer);
}

void Gameboy::debug_run(CPU& cpu) {
    std::string user_input;
    char action;

    uint8_t opcode = cpu.get_opcode_debug();
    cpu.print_line_debug(opcode);
    std::getline(std::cin, user_input);
    std::istringstream iss(user_input);
    iss >> action;

    unsigned num = 1;

    switch (action) {
        case 'h': {
            print_help();
            break;
        }

        case 'c': {
            iss >> num;
            for (unsigned i = 0; i < num; i++) {
                tick(cpu);
            }
            break;
        }

        case 'o': {
            unsigned raw_op;
            iss >> std::hex >> raw_op >> std::dec >> num;
            uint8_t break_op = raw_op & 0xFF;

            for (unsigned i = 0; i < num; i++) {
                // tick once to go past breakpoint
                tick(cpu);
                while (break_op != cpu.get_opcode_debug()) {
                    tick(cpu);
                }
            }
            break;
        }

        case 'b': {
            uint16_t pc_break;
            iss >> std::hex >> pc_break >> std::dec >> num;

            for (unsigned i = 0; i < num; i++) {
                // tick once to go past breakpoint
                tick(cpu);
                while (pc_break != cpu.get_PC_debug()) {
                    tick(cpu);
                }
            }
            break;
        }

        case 'd': {
            cpu.print_debug(opcode);
            break;
        }

        case 'm': {
            uint16_t address;
            iss >> std::hex >> address;
            uint16_t data = mem->read(address, true, true);
            std::cout << utils::hexify8 << +data << " - " << std::dec << +data << '\n' << std::endl;
            break;
        }

        case 'r': {
            cpu.print_mem_debug();
            break;
        }

        case 'i': {
            cpu.print_imm_debug();
            break;
        }

        case 't': {
            timer.timer_debug(std::cout);
            break;
        }

        case 'q': {
            quit = true;
            break;
        }

        default: {
            std::cout << "Command not recognized. Use 'h' for help with a list of commands and their usage" << std::endl;
        }
    }
}

void Gameboy::run(bool debug, bool tilemap) {
    if (mem == nullptr) {
        std::cout << "Bad file name or error while reading file" << std::endl;
        return;
    }

    init_graphics(tilemap);

    CPU cpu = CPU(&interrupts, mem);
    while (!quit) {
        if (!debug) {
            tick(cpu);
        } else {
            debug_run(cpu);
        }
    }

    SDL_DestroyWindow(window);
    SDL_DestroyWindow(tile_window);
    SDL_Quit();
}

void Gameboy::tick(CPU& cpu) {
    unsigned cycles = cpu.tick();
    // Tick memory in case of DMA transfor to OAM
    mem->tick(cycles);
    ppu.run(cycles);
    timer.update_timers(cycles);

    cycle_acc += cycles;
    tick_countdown--;
    if (tick_countdown == 0) {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE) {
                quit = true;
            } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                joypad.parse_key_event(event);
            }
        }

        // Cap FPS
        unsigned curr_time = SDL_GetTicks();
        unsigned time_delta = curr_time - last_time;
        double expected_ms = cycles * 1000 / utils::CLOCK_SPEED;
        int delay = static_cast<unsigned>(expected_ms - time_delta);
        if (delay > 0) {
            SDL_Delay(delay);
        }
        last_time = curr_time;
        cycle_acc = 0;
        tick_countdown = utils::LIMIT_TICKS;
    }
}

void Gameboy::print_help() {
    std::cout << "Command help:\n"
        << "c [num]              - Steps through [num] opcodes\n"
        << "o [hex opcode] [num] - Runs until the specified opcode is reached, optionally [num] times\n"
        << "b [PC value] [num]   - Runs until the program counter reaches the specified value, optionally [num] times\n"
        << "d                    - Debug information\n"
        << "m [hex address]      - Reads 8 bits from the specified address\n"
        << "r                    - Reads 8 bits from the address stored in HL\n"
        << "i                    - Reads 16 bit immediate after the program counter\n"
        << "t                    - Outputs timer debug information\n"
        << "q                    - Quit\n"
        << std::endl;
}