<<<<<<< HEAD
=======
# Generated Cmake Pico project file



set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

>>>>>>> d6fa9ba75ad7200edfe2b27b90da0d01829b6b3d
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
<<<<<<< HEAD
set(PICO_BOARD pico CACHE STRING "Board type")
=======
set(PICO_BOARD pico_w CACHE STRING "Board type")
>>>>>>> d6fa9ba75ad7200edfe2b27b90da0d01829b6b3d

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
<<<<<<< HEAD
project(embarcatech-tarefa-freertos-2 C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(embarcatech-tarefa-freertos-2
    main.c
)

target_include_directories(embarcatech-tarefa-freertos-2 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(embarcatech-tarefa-freertos-2 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    hardware_i2c
    )

pico_add_extra_outputs(embarcatech-tarefa-freertos-2)

# if you have anything in "lib" folder then uncomment below - remember to add a CMakeLists.txt
# file to the "lib" directory
#add_subdirectory(lib)
=======
project(FreeRTOS C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(FreeRTOS 
        src/main.c
        inc/ssd1306_i2c.c
        drivers/buzzer.c
        drivers/display.c
        drivers/joystick.c
 )

pico_set_program_name(FreeRTOS "FreeRTOS")
pico_set_program_version(FreeRTOS "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(FreeRTOS 0)
pico_enable_stdio_usb(FreeRTOS 1)

# Add the standard include files to the build
target_include_directories(FreeRTOS PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/inc
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/headers

)

# Add any user requested libraries
target_link_libraries(FreeRTOS 
        pico_stdlib
        FreeRTOS-Kernel-Heap4
        hardware_adc
        hardware_pwm
        hardware_timer    
        hardware_i2c
        )

pico_add_extra_outputs(FreeRTOS)

# if you have anything in "lib" folder then uncomment below - remember to add a CMakeLists.txt
# file to the "lib" directory
# add_subdirectory(lib)
>>>>>>> d6fa9ba75ad7200edfe2b27b90da0d01829b6b3d
