# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

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
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.12)

# Set any variables required for importing libraries
if (DEFINED ENV{FREERTOS_PATH})
  SET(FREERTOS_PATH $ENV{FREERTOS_PATH})
else()
  SET(FREERTOS_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS-Kernel)
endif()

message("FreeRTOS Kernel located in ${FREERTOS_PATH}")

# Import those libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(FreeRTOS C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(FreeRTOS 
        FreeRTOS.c
        src/main.c
        inc/ssd1306_i2c.c
        drivers/buzzer.c
        drivers/display.c
        drivers/joystick.c
        headers/buzzer.h
        headers/display.h
        headers/joystick.h
        headers/FreeRTOSConfig.h
 )

pico_set_program_name(FreeRTOS "FreeRTOS")
pico_set_program_version(FreeRTOS "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(FreeRTOS 1)
pico_enable_stdio_usb(FreeRTOS 1)

# Add the standard library to the build
target_link_libraries(FreeRTOS
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(FreeRTOS PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/src

)

# Add any user requested libraries
target_link_libraries(FreeRTOS 
        pico_stdlib
        FreeRTOS-Kernel-Heap4
        pico_hardware
        hardware_adc
        hardware_pwm
        hardware_timer    
        hardware_i2c
        )

pico_add_extra_outputs(FreeRTOS)

# if you have anything in "lib" folder then uncomment below - remember to add a CMakeLists.txt
# file to the "lib" directory
# add_subdirectory(lib)