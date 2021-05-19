add_library(cpu STATIC)

target_sources(cpu PRIVATE
    cpu.h
    cpu.cpp
    opcodes.cpp
    opcode_helpers.cpp
    opcode_mappings.cpp
)

target_include_directories(cpu PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(register)
target_link_libraries(cpu
    PUBLIC register
    PRIVATE memory 
    PRIVATE utils
)
