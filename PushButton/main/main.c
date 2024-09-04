#include "hal/gpio_types.h"
#include <stdio.h>
#include <driver/gpio.h>

#include <stdbool.h>


#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_PIN 27
#define BUTTON_PIN 25

#define BUTTON_LOGIC gpio_get_level(BUTTON_PIN)
#define HIGH 1
#define LOW  0

void app_main(void){
	
	/* Config GPIO */
	printf("Push Button Test\n");
	gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
	gpio_set_direction(BUTTON_PIN,GPIO_MODE_INPUT);
	gpio_set_pull_mode(BUTTON_PIN,GPIO_PULLUP_ONLY);
		
	while(true){
		
		if(BUTTON_LOGIC == LOW) /* BC pin is pulled up */
		{
			gpio_set_level(LED_PIN,HIGH);
			printf("LED ON!\n");
		}
		else 
		{
			gpio_set_level(LED_PIN,LOW);
		}
		vTaskDelay(100);	
	}	
}