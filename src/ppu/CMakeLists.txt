target_sources(gameboy 
    PUBLIC
        ppu.h
        ppu.cpp
        ppu_mem.cpp
)

target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})