cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
SET(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(main main.c)
add_executable(led_serial_test led_serial_test.c)
add_executable(button_test button_test.c)
add_executable(analog_test analog_test.c)
add_executable(run_motors_button run_motors_button.c)
add_executable(run_servo_button run_servo_button.c)
add_executable(calibrate_servo calibrate_servo.c)



target_link_libraries(main pico_stdlib hardware_gpio hardware_pwm 
    pico_time pico_cyw43_arch_none hardware_adc)

target_link_libraries(led_serial_test pico_stdlib hardware_gpio pico_cyw43_arch_none)

target_link_libraries(button_test pico_stdlib hardware_gpio pico_cyw43_arch_none)

target_link_libraries(analog_test pico_stdlib hardware_gpio hardware_adc)

target_link_libraries(run_motors_button pico_stdlib hardware_gpio hardware_pwm 
    pico_time pico_cyw43_arch_none hardware_adc)

target_link_libraries(run_servo_button pico_stdlib hardware_gpio hardware_pwm
    pico_cyw43_arch_none)

target_link_libraries(calibrate_servo pico_stdlib hardware_gpio hardware_pwm
    pico_cyw43_arch_none)



pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

pico_enable_stdio_usb(led_serial_test 1)
pico_enable_stdio_uart(led_serial_test 0)

pico_enable_stdio_usb(button_test 1)
pico_enable_stdio_uart(button_test 0)

pico_enable_stdio_usb(analog_test 1)
pico_enable_stdio_uart(analog_test 0)

pico_enable_stdio_usb(run_motors_button 1)
pico_enable_stdio_uart(run_motors_button 0)

pico_enable_stdio_usb(run_servo_button 1)
pico_enable_stdio_uart(run_servo_button 0)

pico_enable_stdio_usb(calibrate_servo 1)
pico_enable_stdio_uart(calibrate_servo 0)


pico_add_extra_outputs(main)
pico_add_extra_outputs(led_serial_test)
pico_add_extra_outputs(button_test)
pico_add_extra_outputs(analog_test)
pico_add_extra_outputs(run_motors_button)
pico_add_extra_outputs(run_servo_button)
pico_add_extra_outputs(calibrate_servo)



