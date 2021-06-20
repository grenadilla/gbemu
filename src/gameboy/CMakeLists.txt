add_library(gameboy STATIC)

target_sources(gameboy PRIVATE
    gameboy.h
    gameboy.cpp
)

target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(gameboy
    PRIVATE utils
    PUBLIC interrupts
    PUBLIC timer
    PUBLIC memory 
    PUBLIC cpu
)
