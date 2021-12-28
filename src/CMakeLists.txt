add_library(gameboy STATIC
    gameboy.h
    gameboy.cpp
)

find_package(SDL2 REQUIRED)

target_include_directories(gameboy 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
    PUBLIC ${SDL2_INCLUDE_DIRS}    
)

target_link_libraries(gameboy PUBLIC ${SDL2_LIBRARIES})

add_subdirectory(utils)
add_subdirectory(interrupts)
add_subdirectory(apu)
add_subdirectory(ppu)
add_subdirectory(joypad)
add_subdirectory(timer)
add_subdirectory(memory)
add_subdirectory(cpu)