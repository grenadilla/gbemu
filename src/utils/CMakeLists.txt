add_library(utils STATIC)

target_sources(utils PRIVATE
    utils.h
    utils.cpp
)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_LIST_DIR})
