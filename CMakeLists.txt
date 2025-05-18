# Sets minimum version for CMake
cmake_minimum_required(VERSION 3.13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if(EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Setting type of the board
set(PICO_BOARD pico CACHE STRING "Board type")

# Initializing the Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# For Project set up
project(treasure_Robo C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Raspberry Pi Pico SDK initilization
pico_sdk_init()

# Add compilation subdirectory
add_subdirectory(Library/infared)
add_subdirectory(Library/motor)
add_subdirectory(Library/servo)
add_subdirectory(Library/ultrasonic)
add_subdirectory(Library/motor/MotorDriver/Config)
add_subdirectory(Library/motor/MotorDriver/Devices)

# Add header file directory
include_directories(Library/motor/MotorDriver/Devices)
include_directories(Library/motor/MotorDriver/Config)
include_directories(Library/motor)
include_directories(Library/ultrasonic)
include_directories(Library/infared)
include_directories(Library/servo)



add_executable(treasure_Robo
    main.cpp
    Library/motor/motor.cpp
    Library/ultrasonic/ultrasonic.cpp
    Library/infared/infrared.cpp
    Library/servo/servo.cpp
    Library/servo/pico_servo.c
    Library/motor/MotorDriver/Devices/MotorDriver.c
    Library/motor/MotorDriver/Devices/PCA9685.c
    Library/motor/MotorDriver/Config/DEV_Config.c

)

#Includes supportive directories
target_include_directories(treasure_Robo PRIVATE ${CMAKE_CURRENT_LIST_DIR}/inc)

#Linking Pico SDK libraries
target_link_libraries(treasure_Robo ultrasonic infrared servo motor Config Devices pico_stdlib hardware_i2c hardware_pwm hardware_gpio)

# USB output, disable UART output
pico_enable_stdio_usb(treasure_Robo 1)
pico_enable_stdio_uart(treasure_Robo 0)

#For creating a UF2 file for flashing
pico_add_extra_outputs(treasure_Robo)


find_program(CLANG_FORMAT NAMES clang-format clang-format-18)
if(CLANG_FORMAT AND NOT (CLANG_FORMAT MATCHES "NOTFOUND"))
        message("Clang-format found ${CLANG_FORMAT}")
        add_custom_target(
                format
                COMMAND ${CLANG_FORMAT} --style=file --dry-run source_file
)
endif()

#For enabling warnings
target_compile_options(treasure_Robo PRIVATE 
    # Warnings
    $<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Werror;-Wshadow;>
    $<$<CXX_COMPILER_ID:Clang>:-Wall;-Wextra;-Werror;-Wshadow;>
    $<$<CXX_COMPILER_ID:AppleClang>:-Wall;-Wextra;-Werror;-Wshadow;>
    $<$<CXX_COMPILER_ID:MSVC>:/W4;/WX;/w14265>

    # Optimizations
    $<$<CONFIG:Release>:$<$<CXX_COMPILER_ID:GNU>:-O3>>
    $<$<CONFIG:Release>:$<$<CXX_COMPILER_ID:Clang>:-O3>>
    $<$<CONFIG:Release>:$<$<CXX_COMPILER_ID:AppleClang>:-O3>>
    $<$<CONFIG:Release>:$<$<CXX_COMPILER_ID:MSVC>:/O2>>

    # Debug settings (consolidated)
    $<$<CONFIG:Debug>:$<$<CXX_COMPILER_ID:GNU>:-O0;-g;-fno-omit-frame-pointer>>
    $<$<CONFIG:Debug>:$<$<CXX_COMPILER_ID:Clang>:-O0;-g;-fno-omit-frame-pointer>>
    $<$<CONFIG:Debug>:$<$<CXX_COMPILER_ID:AppleClang>:-O0;-g;-fno-omit-frame-pointer>>
    $<$<CONFIG:Debug>:$<$<CXX_COMPILER_ID:MSVC>:/Od;/Zi;/RTC1;/Oy->>
)

# include(test/test.cmake)