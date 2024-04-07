
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "pico/multicore.h"
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

    pwm_set_gpio_level(8, 900);

    sleep_ms(1000);

    pwm_set_gpio_level(2, 488);
    pwm_set_gpio_level(4, 488);
    pwm_set_gpio_level(6, 488);

    sleep_ms(5000);

    for (int i = 0; i < 180; i++) {
        pwm_set_gpio_level(8, 976 + (i*976)/180);
        sleep_ms(10);
    }
    while (1) {
        tight_loop_contents();;
    }
}
