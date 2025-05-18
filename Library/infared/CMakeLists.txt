cmake_minimum_required(VERSION 3.10.0)
project(infrared VERSION 0.1.0 LANGUAGES C CXX)

add_library(infrared
    infrared.cpp
)

target_include_directories(infrared PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link with pico_stdlib
target_link_libraries(infrared pico_stdlib)
