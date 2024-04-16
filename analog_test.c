#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/binary_info.h"

const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;

int main() {
    bi_decl(bi_program_description("Test button"));

    stdio_init_all();

    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);
    adc_set_round_robin(0b00111);
    adc_select_input(26);
    while (1) {
        printf("26: %d\n", adc_read());
        printf("27: %d\n", adc_read());
        printf("28: %d\n", adc_read());
        sleep_ms(10);
    }
}

