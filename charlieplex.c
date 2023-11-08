#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

#define ON_BOARD_PIN 25;
#define NUMBER_OF_LEDS 5;
int pins[] = {20, 21, 22};

int led_pin_states[5][3] = 
{
    {1, 0, -1},
    {0, 1, -1},
    {-1, 1, 0},
    {-1, 0, 1},
    {1, -1, 0}
};

int led_states[5];

int arraySize(int array[]){
    return sizeof(array) / sizeof(array[0]);
}

void setPins(int led){
    for(int pin = 0; pin < arraySize(pins); pin++){
        uint gpio_pin = pins[pin];

        if(led_pin_states[led][pin] == -1)
        {
            gpio_set_dir(gpio_pin, GPIO_IN);
        }
        else{
            gpio_set_dir(gpio_pin, GPIO_OUT);
            gpio_put(gpio_pin, led_pin_states[led][pin]);
        }
    }
}

void clearPins(){
    for(int pin = 0; pin < arraySize(pins); pin++){
        uint gpio_pin = pins[pin];
        gpio_set_dir(gpio_pin, GPIO_IN);
    }
}

void refresh(){
    for(int led = 0; led < arraySize(led_states); led++){
        clearPins();
        if(led_states[led]){
            setPins(led);
        }
        sleep_ms(5);
    }
}

int main() {
    stdio_init_all();
    uint LED_PIN = ON_BOARD_PIN;
    gpio_init(LED_PIN);

    gpio_set_dir(LED_PIN, GPIO_OUT);
    bool on_board_pin_state = true;
    //turn on ON_BOARD_PIN

    for(int pin = 0; pin < arraySize(pins); pin++){
        uint gpio_pin = pins[pin];
        gpio_init(gpio_pin);
    }
    
    int index = 0;
    int number_of_leds = NUMBER_OF_LEDS;
    while (true) {

        gpio_put(LED_PIN, on_board_pin_state);
        printf("Hello, world!\n");
        int led = rand() % (number_of_leds + 1);
        printf("Toggling led: %d\n", led);
        led_states[led] = !led_states[led];
        
        refresh();
        sleep_ms(1000);
        on_board_pin_state = !on_board_pin_state;
    }
}
