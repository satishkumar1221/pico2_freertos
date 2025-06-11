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
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
#include(${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2350_ARM_NTZ/FreeRTOS_Kernel_import.cmake)
include(FreeRTOS_Kernel_import.cmake)
project(pico_freertos C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()
#include directories for header files
#include_directories(${CMAKE_SOURCE_DIR}/OS_Config ${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2350_ARM_NTZ/non_secure)

# Add executable. Default name is the project name, version 0.1
add_subdirectory(Os_Config)
add_subdirectory(HAL)

add_executable(pico_freertos pico_freertos.cpp 
                             freertos_os_wrapper.cpp 
                             task_20ms_c0.cpp task_50ms_c0.cpp 
                             task_100ms_c0.cpp 
                             task_1000ms_c0.cpp 
                             task_2000ms_c0.cpp)

pico_set_program_name(pico_freertos "pico_freertos")
pico_set_program_version(pico_freertos "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico_freertos 0)
pico_enable_stdio_usb(pico_freertos 0)



# Add the standard include files to the build
target_include_directories(pico_freertos PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/OS_Config 
        ${CMAKE_CURRENT_LIST_DIR}/HAL
        ${CMAKE_CURRENT_LIST_DIR}/HAL/ADC
        ${CMAKE_CURRENT_LIST_DIR}/HAL/DMA
        ${CMAKE_CURRENT_LIST_DIR}/HAL/DIO
        ${CMAKE_CURRENT_LIST_DIR}/HAL/I2C 
         ${CMAKE_CURRENT_LIST_DIR}/HAL/SPI
        ${CMAKE_CURRENT_LIST_DIR}/HAL/UART   
        ${PROJECT_SOURCE_DIR}
)

# Add the standard library to the build
target_link_libraries(pico_freertos
        pico_stdlib FreeRTOS-Kernel-Heap4 OS_Lib HAL_Lib)



pico_add_extra_outputs(pico_freertos)

