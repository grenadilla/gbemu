target_sources(gameboy 
    PUBLIC
        mbc0.h
        mbc0.cpp
        mbc1.h
        mbc1.cpp
)
target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_LIST_DIR})