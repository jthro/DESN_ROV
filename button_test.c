#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "pico/cyw43_arch.h"

const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;

int main() {
    bi_decl(bi_program_description("Test button"));
    bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

    stdio_init_all();
    if(cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    gpio_init(8);
    gpio_set_dir(8, GPIO_IN);
    gpio_pull_up(8);

    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

    while (1) {
        if (!gpio_get(8)) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            puts("button pressed");
        } else {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }
        sleep_ms(100);
    }
}

