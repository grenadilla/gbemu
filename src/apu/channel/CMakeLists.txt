target_sources(gameboy 
    PUBLIC
        channel.h
        channel.cpp
        channel_mem.cpp
)
target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})