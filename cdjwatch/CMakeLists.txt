# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(cdjwatch C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_subdirectory(./lib/Config)
add_subdirectory(./lib/LCD)
add_subdirectory(./lib/Touch)
add_subdirectory(./lib/QMI8658)
add_subdirectory(./lib/lvgl)

include_directories(./lib/Config)
include_directories(./lib/LCD)
include_directories(./lib/Touch)
include_directories(./lib/QMI8658)
include_directories(./lib/lvgl)

add_executable(cdjwatch
                main.c
                logo_cdj_belgium_transparent_100_100.c)

pico_set_program_name(cdjwatch  "Coderdojo Watch")
pico_set_program_version(cdjwatch "0.1")

pico_enable_stdio_uart(cdjwatch 1)
pico_enable_stdio_usb(cdjwatch 0)

# Add the standard library to the build

set(LV_CONF_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/LVGL/lv_conf.h
    CACHE STRING "" FORCE)
add_compile_options(-O2)


target_link_libraries(cdjwatch
                        LCD
                        Touch
                        QMI8658
                        LVGL
                        Config
                        pico_stdlib
                        hardware_spi
                        hardware_i2c
                        hardware_dma
                        )

# Add the standard include files to the build
target_include_directories(cdjwatch   PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(cdjwatch)

