cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(autonomous_car_project)

# Initialize the SDK
pico_sdk_init()

# Add all library subdirectories
add_subdirectory(Library/infared)
add_subdirectory(Library/motor)
add_subdirectory(Library/servo)
add_subdirectory(Library/ultrasonic)

# Create executable
add_executable(main
    main.cpp
)

# Include directories if needed
target_include_directories(main PRIVATE
    Library/infared
    Library/motor
    Library/servo
    Library/ultrasonic
)

# Link libraries
target_link_libraries(main
    pico_stdlib
    hardware_pwm
    hardware_gpio
    hardware_i2c
    motor
    servo
    ultrasonic
    infrared
)

# Create UF2 file
pico_add_extra_outputs(main)
