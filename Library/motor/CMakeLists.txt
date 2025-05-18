cmake_minimum_required(VERSION 3.10)

project(motor LANGUAGES CXX)

add_library(motor motor.cpp)

target_include_directories(motor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../MotorDriver/Devices
        ${CMAKE_CURRENT_SOURCE_DIR}/../MotorDriver/Config
        ${PICO_SDK_PATH}/src/common/include
        ${PICO_SDK_PATH}/src/boards/include
        ${PICO_SDK_PATH}/src/rp2_common/hardware_spi/include
        ${PICO_SDK_PATH}/src/rp2_common/hardware_i2c/include
        ${PICO_SDK_PATH}/src/rp2_common/hardware_pwm/include
        ${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
        ${PICO_SDK_PATH}/src/rp2_common/pico_stdlib/include
)

target_link_libraries(motor
    PUBLIC
        Devices
        pico_stdlib
)