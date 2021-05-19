add_library(cpu STATIC)

target_sources(cpu PRIVATE
    cpu.h
    cpu.cpp
    register.cpp
    register.h
    opcodes.cpp
    opcode_helpers.cpp
    opcode_mappings.cpp
)
target_include_directories(cpu PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(cpu memory utils)