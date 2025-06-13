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
include_directories("${PICO_SDK_PATH}/pico-sdk/src/common/pico_base/include")
#include_directories(${CMAKE_SOURCE_DIR})

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# Add executable. Default name is the project name, version 0.1
# Add the standard include files to the build
include_directories(
                    ${CMAKE_CURRENT_LIST_DIR}/API_LIB
                    ${CMAKE_CURRENT_LIST_DIR}/Mem_Lib
                    ${CMAKE_SOURCE_DIR}
                    ${PICO_SDK_PATH}/pico-sdk/src/common/pico_base/include
)

set(SOURCES 
   {CMAKE_CURRENT_LIST_DIR}/API_LIB/apilib.cpp
   {CMAKE_CURRENT_LIST_DIR}/Mem_Lib/memlib.cpp
)
#set sources and add_executable

message(STATUS "CMAKE_CURRENT_LIST_DIR: ${CMAKE_CURRENT_LIST_DIR}")

add_library(Infra_Lib 
           ${CMAKE_CURRENT_LIST_DIR}/Mem_Lib/memlib.cpp
           ${CMAKE_CURRENT_LIST_DIR}/API_LIB/apilib.cpp
)

target_include_directories(Infra_Lib PUBLIC "${CMAKE_CURRENT_LIST_DIR}")


file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/**/*.h")


#include the target dorectories








# Pull in our pico_stdlib which pulls in commonly used features







