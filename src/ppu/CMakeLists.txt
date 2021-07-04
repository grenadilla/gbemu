add_library(ppu STATIC)

target_sources(ppu PRIVATE
    ppu.h
    ppu_mem.cpp
)
target_include_directories(ppu PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(ppu PUBLIC utils)