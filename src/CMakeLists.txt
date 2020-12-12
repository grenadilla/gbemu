add_library(srcfiles "")
# CMAKE_CURRENT_SOURCE_DIR
target_sources(srcfiles PRIVATE 
    cpu.h
    cpu.cpp
    register.cpp
    register.h
    opcodes.cpp
    opcode_helpers.cpp
    opcode_mappings.cpp
)
target_include_directories(srcfiles PUBLIC ${CMAKE_CURRENT_LIST_DIR})
