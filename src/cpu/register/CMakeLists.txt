target_sources(gameboy 
    PUBLIC
        register.h
        register.cpp
)
target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})