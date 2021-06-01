add_library(interrupts STATIC)

target_sources(interrupts PRIVATE
    interrupts.h
    interrupts.cpp
)
target_include_directories(interrupts PUBLIC ${CMAKE_CURRENT_LIST_DIR})