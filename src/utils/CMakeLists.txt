target_sources(gameboy 
    PUBLIC
        utils.h
    PRIVATE
        utils.cpp
)
target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})
