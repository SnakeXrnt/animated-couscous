cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(Pico_ePaper_Code)
pico_sdk_init()

# Add compilation subdirectory
add_subdirectory(lib/Config)
add_subdirectory(lib/Devices)
add_subdirectory(examples)

# Add header file directory
include_directories(examples)
include_directories(./lib/Config)
include_directories(./lib/Devices)

# Generate executable file
add_executable(main 
main.c
)

# enable usb output, disable uart output
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

target_link_libraries(main examples Config pico_stdlib Devices hardware_i2c)