add_library(register STATIC)

target_sources(register PRIVATE
    register.h
    register.cpp
)
target_include_directories(register PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(register PRIVATE utils)