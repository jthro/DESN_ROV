
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
    bi_decl(bi_program_description("This is a test binary."));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    gpio_init(8);
    gpio_set_dir(8, GPIO_IN);
    gpio_pull_up(8);

    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);
    adc_set_round_robin(0b00111);
    adc_select_input(26);

    gpio_set_function(0, GPIO_FUNC_PWM);
    gpio_set_function(4, GPIO_FUNC_PWM);
    gpio_set_function(6, GPIO_FUNC_PWM);
    gpio_set_function(10, GPIO_FUNC_PWM);

    uint slice_num_0 = pwm_gpio_to_slice_num(0);
    uint slice_num_4 = pwm_gpio_to_slice_num(4);
    uint slice_num_6 = pwm_gpio_to_slice_num(6);
    uint slice_num_10 = pwm_gpio_to_slice_num(10);

    pwm_set_clkdiv(slice_num_0, 256.f);
    pwm_set_clkdiv(slice_num_4, 256.f);
    pwm_set_clkdiv(slice_num_6, 256.f);
    pwm_set_clkdiv(slice_num_10, 64.f);

    pwm_set_wrap(slice_num_0, 976.f);
    pwm_set_wrap(slice_num_4, 976.f);
    pwm_set_wrap(slice_num_6, 976.f);

    pwm_set_wrap(slice_num_10, 7812.f);

    pwm_set_enabled(slice_num_0, true);
    pwm_set_enabled(slice_num_4, true);
    pwm_set_enabled(slice_num_6, true);

    pwm_set_enabled(slice_num_10, true);

    pwm_set_gpio_level(0, 976.f);
    pwm_set_gpio_level(4, 976.f);
    pwm_set_gpio_level(6, 976.f);

    pwm_set_gpio_level(10, 936.f);

    sleep_ms(2500);

    pwm_set_gpio_level(0, 488.f);
    pwm_set_gpio_level(4, 488.f);
    pwm_set_gpio_level(6, 488.f);

    sleep_ms(2000);

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

        while (1) {
        if (!gpio_get(8)) {
            pwm_set_gpio_level(10, 3250.f);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        } else {
            pwm_set_gpio_level(10, 2500.f);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        }
        pwm_set_gpio_level(0, (float)(488 + 488 * (adc_read() - 300) / 4096));
        pwm_set_gpio_level(4, (float)(488 + 488 * (adc_read() - 30) / 4096));
        pwm_set_gpio_level(6, (float)(488 + 488 * (adc_read() - 80) / 4096));

        sleep_ms(10);
   }
}
