# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==

# ====================================================================================
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#include(${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel/portable/ThirdParty/GCC/RP2350_ARM_NTZ/FreeRTOS_Kernel_import.cmake)

#include_directories(${CMAKE_SOURCE_DIR})

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# Add executable. Default name is the project name, version 0.1
# Add the standard include files to the build
#set sources and add_executable

include_directories(${CMAKE_CURRENT_LIST_DIR}/ADC
{CMAKE_CURRENT_LIST_DIR}/DIO
{CMAKE_CURRENT_LIST_DIR}/I2C
{CMAKE_CURRENT_LIST_DIR}/SPI
{CMAKE_CURRENT_LIST_DIR}/UART
{CMAKE_CURRENT_LIST_DIR}/DMA
)
set(SOURCES {CMAKE_CURRENT_LIST_DIR}/ADC/adc_cfg.cpp
{CMAKE_CURRENT_LIST_DIR}/DIO/dio_cfg.cpp
{CMAKE_CURRENT_LIST_DIR}/I2C/i2c_cfg.cpp
{CMAKE_CURRENT_LIST_DIR}/SPI/spi_cfg.cpp
{CMAKE_CURRENT_LIST_DIR}/UART/uart_cfg.cpp
{CMAKE_CURRENT_LIST_DIR}/DMA/dma_cfg.cpp
{CMAKE_CURRENT_LIST_DIR}/UART/uart.cpp
{CMAKE_CURRENT_LIST_DIR}/ADC/adc.cpp
{CMAKE_CURRENT_LIST_DIR}/DIO/dio.cpp
{CMAKE_CURRENT_LIST_DIR}/I2C/i2c.cpp
{CMAKE_CURRENT_LIST_DIR}/SPI/spi.cpp
{CMAKE_CURRENT_LIST_DIR}/DMA/dma.cpp

)

add_library(HAL_Lib
           ${CMAKE_CURRENT_LIST_DIR}/DIO/dio_cfg.cpp
           ${CMAKE_CURRENT_LIST_DIR}/DIO/dio.cpp
           ${CMAKE_CURRENT_LIST_DIR}/I2C/i2c_cfg.cpp
           ${CMAKE_CURRENT_LIST_DIR}/I2C/i2c.cpp
           ${CMAKE_CURRENT_LIST_DIR}/SPI/spi_cfg.cpp
           ${CMAKE_CURRENT_LIST_DIR}/SPI/spi.cpp
           ${CMAKE_CURRENT_LIST_DIR}/UART/uart_cfg.cpp
           ${CMAKE_CURRENT_LIST_DIR}/UART/uart.cpp
           ${CMAKE_CURRENT_LIST_DIR}/DMA/dma_cfg.cpp
           ${CMAKE_CURRENT_LIST_DIR}/DMA/dma.cpp
           ${CMAKE_CURRENT_LIST_DIR}/ADC/adc_cfg.cpp
           ${CMAKE_CURRENT_LIST_DIR}/ADC/adc.cpp
)

file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/**/*.h")
#include the target dorectories




include_directories(HAL PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/ADC
        ${CMAKE_CURRENT_LIST_DIR}/DIO
        ${CMAKE_CURRENT_LIST_DIR}/I2C
        ${CMAKE_CURRENT_LIST_DIR}/SPI
        ${CMAKE_CURRENT_LIST_DIR}/UART
)



# Pull in our pico_stdlib which pulls in commonly used features







