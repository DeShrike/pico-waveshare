cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
#include(pico_extras_import.cmake)
# set(PICO_BOARD pico_w)
project(matrix C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(matrix
        matrix.c
		pico7219.c
        )

pico_set_program_name(matrix  "Matrix Test")
pico_set_program_version(matrix "0.1")

target_link_libraries(matrix PRIVATE
        pico_stdlib
        hardware_spi
        hardware_adc
#        pico_audio_i2s
        )

# Add the standard include files to the build
target_include_directories(matrix   PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_definitions(matrix PRIVATE
        # compile time configuration of I2S
        PICO_AUDIO_I2S_MONO_INPUT=0
        #define for our example code
        USE_AUDIO_I2S=0
#            PICO_AUDIO_I2S_DATA_PIN=22
#            PICO_AUDIO_I2S_CLOCK_PIN_BASE=23
#            PICO_DEFAULT_UART=0
#            PICO_DEFAULT_UART_TX_PIN=28
#            PICO_DEFAULT_UART_RX_PIN=29
        )
# enable usb output, disable uart output
pico_enable_stdio_usb(matrix 1)
pico_enable_stdio_uart(matrix 0)
# create map/bin/hex file etc.
pico_add_extra_outputs(matrix)

