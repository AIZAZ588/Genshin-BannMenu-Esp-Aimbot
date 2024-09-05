#include "hal/gpio_types.h"
#include "soc/gpio_num.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <driver/gpio.h>

gpio_config_t led_gpios;

#define LED1 GPIO_NUM_33
#define LED2 GPIO_NUM_25
#define LED3 GPIO_NUM_26

void app_main(void)
{
	led_gpios.pin_bit_mask = (LED1) | (1<<LED2) | (1<<LED3);
	led_gpios.mode = GPIO_MODE_OUTPUT;
	led_gpios.intr_type = GPIO_INTR_DISABLE;
	led_gpios.pull_up_en = GPIO_PULLUP_DISABLE;
	led_gpios.pull_down_en = GPIO_PULLDOWN_DISABLE;
	
	gpio_config(&led_gpios);
	
	
    while (true) {
        printf("Hello from app_main!\n");
        gpio_set_level(LED1, 0);
        gpio_set_level(LED2, 0);
        gpio_set_level(LED3, 0);
        
        sleep(1);
        
        gpio_set_level(LED1, 1);
        gpio_set_level(LED2, 1);
        gpio_set_level(LED3, 1);
        
        sleep(1);
        
    }
}
