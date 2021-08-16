target_sources(gameboy 
    PUBLIC
        memory.h
        memory.cpp
        hardware_registers.cpp
)

target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(mbc)
