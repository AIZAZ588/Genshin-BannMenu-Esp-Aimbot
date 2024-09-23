#include <hal/gpio_types.h>
#include<stdio.h>
#include<stdbool.h>
#include<unistd.h>

#include<driver/gpio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

#define LED_PIN 23

void app_main(void){
	
	gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT);
	while(true){
		printf("Hello Aizaz\n");
		gpio_set_level(LED_PIN,0);
		sleep(1);
		gpio_set_level(LED_PIN,1);
		sleep(1);
	}
}