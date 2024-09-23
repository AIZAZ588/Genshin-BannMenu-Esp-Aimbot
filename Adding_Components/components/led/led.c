#include "led.h"
#include "driver/gpio.h"

void trunOnLED(void){
    gpio_set_direction(5,GPIO_MODE_OUTPUT);
    gpio_set_level(5,1);
    printf("LED ON!\n");

}