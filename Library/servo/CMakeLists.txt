cmake_minimum_required(VERSION 3.10.0)
project(servo VERSION 0.1.0 LANGUAGES C CXX)

add_library(servo
    servo.cpp
    pico_servo.c
)

target_include_directories(servo PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PICO_SDK_PATH}/src/common/include
    ${PICO_SDK_PATH}/src/boards/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_pwm/include
    ${PICO_SDK_PATH}/src/rp2_common/hardware_gpio/include
    ${PICO_SDK_PATH}/src/rp2_common/pico_stdlib/include
)

# Link with pico_stdlib
target_link_libraries(servo pico_stdlib)
