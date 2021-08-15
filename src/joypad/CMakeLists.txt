target_sources(gameboy 
    PUBLIC
        joypad.h
        joypad.cpp
)

target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})