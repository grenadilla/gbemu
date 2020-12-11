add_library(srcfiles "")
target_sources(srcfiles PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/cpu.h
    ${CMAKE_CURRENT_SOURCE_DIR}/cpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/register.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/register.h
    ${CMAKE_CURRENT_SOURCE_DIR}/opcodes.cpp
)
target_include_directories(srcfiles PUBLIC ${CMAKE_CURRENT_LIST_DIR})
