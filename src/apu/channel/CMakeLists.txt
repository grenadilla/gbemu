target_sources(gameboy 
    PUBLIC
        channel.h
        channel.cpp
        channel_mem.cpp
        wave_channel.h
        wave_channel.cpp
)
target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})