#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"

#define ON_BOARD_PIN 25;
#define NUMBER_OF_LEDS 5;

int pins_array_size = 3;
static int led_states_array_size = 5;
int pins[] = {20, 21, 22};
char *led_colors[5] = {"Bue", "Red", "White", "Green", "Yellow"};
int led_pin_states[5][3] = 
{

    {1, -1, 0}, //Blue
    {0, -1, 1}, //Red
    {1, 0, -1}, //White
    {0, 1, -1}, //Green
    {-1, 1, 0}, //Yellow
};

int led_states[5];

void setPins(int led){
    for(int pin = 0; pin < pins_array_size; pin++){
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
    for(int pin = 0; pin < pins_array_size; pin++){
        uint gpio_pin = pins[pin];
        gpio_set_dir(gpio_pin, GPIO_IN);
    }
}

void refresh(){

    clearPins();
    for(int led = 0; led < (int)led_states_array_size; led++){
        if(led_states[led]){
            setPins(led);
        }
        sleep_ms(5);
    }
}

void clearLedStates(){
for(int led = 0; led < led_states_array_size; led++){
        clearPins();
        if(led_states[led]){
            led_states[led] = !led_states[led];
        }
    }
}

int main() {
    stdio_init_all();
    uint LED_PIN = ON_BOARD_PIN;
    gpio_init(LED_PIN);

    gpio_set_dir(LED_PIN, GPIO_OUT);
    bool on_board_pin_state = true;
    //turn on ON_BOARD_PIN

    for(int pin = 0; pin < pins_array_size; pin++){
        uint gpio_pin = pins[pin];
        gpio_init(gpio_pin);
    }
    
    int number_of_leds = NUMBER_OF_LEDS;
    int current_led = -1;
    while (true) {

        gpio_put(LED_PIN, on_board_pin_state);
        printf("Hello, world!\n");
        int led = rand() % (number_of_leds);
        while(led == current_led){
            led = rand() % (number_of_leds);
        }

        current_led = led;

        printf("Toggling led: %s\n", led_colors[led]);
        clearLedStates();
        led_states[led] = !led_states[led];
        
        refresh();
        sleep_ms(995);
        on_board_pin_state = !on_board_pin_state;
    }
}
