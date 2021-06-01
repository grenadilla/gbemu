add_library(memory STATIC)

target_sources(memory PRIVATE
    memory.h
    memory.cpp
    hardware_registers.cpp
)
target_include_directories(memory PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(memory PRIVATE utils)
target_link_libraries(memory PUBLIC timer interrupts)