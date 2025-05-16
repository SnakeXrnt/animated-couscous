cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(TresureRobot VERSION 0.1.0 LANGUAGES C CXX)

pico_sdk_init()

add_executable(TresureRobot
    main.cpp
)

# Add library subdirectories
add_subdirectory(Library/infared)
add_subdirectory(Library/motor)
add_subdirectory(Library/servo)
add_subdirectory(Library/ultrasonic)

# Link libraries to the executable
target_link_libraries(TresureRobot
    PRIVATE
        pico_stdlib
        infared
        motor
        servo
        ultrasonic
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(TresureRobot 1)
pico_enable_stdio_uart(TresureRobot 0)

# Create UF2 file for Pico
pico_add_extra_outputs(TresureRobot)