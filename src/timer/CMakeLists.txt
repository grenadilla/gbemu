target_sources(gameboy 
    PUBLIC
        timer.h
        timer.cpp
)

target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})
