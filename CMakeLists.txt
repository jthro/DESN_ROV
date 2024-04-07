cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(main main.c)

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

pico_add_extra_outputs(main)

target_link_libraries(main pico_stdlib hardware_gpio hardware_pwm 
    pico_time pico_cyw43_arch_none hardware_adc)
