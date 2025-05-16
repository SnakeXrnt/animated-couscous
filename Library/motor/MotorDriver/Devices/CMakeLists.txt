# Search for all source files in the current directory
# and save the names to the DIR_Pico_Servo_Driver_SRCS variable
aux_source_directory(. DIR_Pico_Servo_Driver_SRCS)

include_directories(../Config)

# Generate link library
add_library(Devices ${DIR_Pico_Servo_Driver_SRCS})
target_link_libraries(Devices PUBLIC Config)