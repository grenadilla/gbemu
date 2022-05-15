target_sources(gameboy 
    PUBLIC
        apu.h
        apu.cpp
        apu_mem.cpp
)

target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(channel)