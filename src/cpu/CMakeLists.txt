target_sources(gameboy
    PUBLIC
        cpu.h
        cpu.cpp
        debug.cpp
        opcodes.cpp
        opcode_helpers.cpp
        opcode_mappings.cpp
)

target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(register)
