
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "pico/binary_info.h"
#include "pico/time.h"
#include "pico/cyw43_arch.h"

const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;

int main() {
    bi_decl(bi_program_description("Main"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);
    adc_set_round_robin(0b00111);
    adc_select_input(26);

    gpio_init(20);
    gpio_set_dir(20, GPIO_IN);
    gpio_pull_up(20);

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    gpio_set_function(2, GPIO_FUNC_PWM);
    gpio_set_function(4, GPIO_FUNC_PWM);
    gpio_set_function(6, GPIO_FUNC_PWM);
    gpio_set_function(8, GPIO_FUNC_PWM);
    
    uint slice_num_2 = pwm_gpio_to_slice_num(2);
    uint slice_num_4 = pwm_gpio_to_slice_num(4);
    uint slice_num_6 = pwm_gpio_to_slice_num(6);
    uint slice_num_8 = pwm_gpio_to_slice_num(8);

    pwm_set_clkdiv(slice_num_2, 256.f);
    pwm_set_clkdiv(slice_num_4, 256.f);
    pwm_set_clkdiv(slice_num_6, 256.f);
    pwm_set_clkdiv(slice_num_8, 256.f);

    pwm_set_enabled(slice_num_2, true);
    pwm_set_enabled(slice_num_4, true);
    pwm_set_enabled(slice_num_6, true);
    pwm_set_enabled(slice_num_8, true);

    pwm_set_wrap(slice_num_2, 976);
    pwm_set_wrap(slice_num_4, 976);
    pwm_set_wrap(slice_num_6, 976);
    pwm_set_wrap(slice_num_8, 1953);

    pwm_set_gpio_level(2, 976);
    pwm_set_gpio_level(4, 976);
    pwm_set_gpio_level(6, 976);

    pwm_set_gpio_level(8, 1953);

    sleep_ms(1000);

    pwm_set_gpio_level(2, 489);
    pwm_set_gpio_level(4, 489);
    pwm_set_gpio_level(6, 489);

    sleep_ms(3000);

    double servo_duty_cycle = 1465;
    double left_duty_cycle = 489;
    double vertical_duty_cycle = 489;
    double right_duty_cycle = 489;


    while (1) {
        if (!gpio_get(20)) {
            servo_duty_cycle = 1400.f;
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

        } else {
            servo_duty_cycle = 976.f;
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

        }
        printf("%d\n", servo_duty_cycle);
        vertical_duty_cycle = 489 + 489 * (adc_read() / 4000);
        left_duty_cycle = 489 + 489 * (adc_read() / 4000);
        right_duty_cycle = 489 + 489 * (adc_read()  / 4000);


        pwm_set_gpio_level(8, servo_duty_cycle);
        pwm_set_gpio_level(2, left_duty_cycle);
        pwm_set_gpio_level(4, right_duty_cycle);
        pwm_set_gpio_level(6, vertical_duty_cycle);
        sleep_ms(10);
   }
}
