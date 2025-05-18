cmake_minimum_required(VERSION 3.10.0)
project(ultrasonic VERSION 0.1.0 LANGUAGES C CXX)

add_library(ultrasonic
    ultrasonic.cpp
)

target_include_directories(ultrasonic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link with pico_stdlib
target_link_libraries(ultrasonic pico_stdlib)
