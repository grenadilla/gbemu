add_library(timer STATIC)

target_sources(timer PRIVATE
    timer.h
    timer.cpp
)
target_include_directories(timer PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(timer PRIVATE utils)
target_link_libraries(timer PUBLIC interrupts)
