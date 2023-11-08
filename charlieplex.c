#include <stdio.h>
#include "pico/stdlib.h"

#define ON_BOARD_PIN 25;


int main() {
    stdio_init_all();
    const uint LED_PIN = ON_BOARD_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    //turn on ON_BOARD_PIN
    gpio_put(LED_PIN, true);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
