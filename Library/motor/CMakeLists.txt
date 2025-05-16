cmake_minimum_required(VERSION 3.10)

project(motor LANGUAGES CXX)

add_library(motor motor.cpp)

target_include_directories(motor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../MotorDriver/Devices
        ${CMAKE_CURRENT_SOURCE_DIR}/../MotorDriver/Config
)

target_link_libraries(motor
    PUBLIC
        Devices
)