target_sources(gameboy 
    PUBLIC
        interrupts.h
        interrupts.cpp
)
target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})