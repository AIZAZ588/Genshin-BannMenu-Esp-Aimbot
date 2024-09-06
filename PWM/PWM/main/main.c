/*
					LED Control (LEDC)
	primarily designed to control the intensity of LEDs
	
	PWM  : Pulse width modulation
		 : LEDC Channel divide into two groups  8 channel each
		 : one high speed group, offers glitch free duty cycle
		 : 2nd low  speed group
		 
		 		Steps for Configuring PWM
	1    : Timer 	Configuration
	2    : Channel  Configuration
	3    : PWM		Configuration
	
						URL
	   
	*    : https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/ledc.html?highlight=pwm
	*    : https://esp32tutorials.com/esp32-pwm-esp-idf-led-brightness-control/	
*/

/* libraries */
#include "hal/ledc_types.h"
#include "soc/clk_tree_defs.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/ledc.h>

#define LED GPIO_NUM_27
#define delayms(x) vTaskDelay(x/portTICK_PERIOD_MS)

void app_main(void){
	
	
	/* Step 1 : Timer Configuration */
	ledc_timer_config_t ledc_timer = {
		.duty_resolution = LEDC_TIMER_10_BIT,
		.freq_hz		 = 1000,
		.speed_mode		 = LEDC_HIGH_SPEED_MODE,
		.clk_cfg		 = LEDC_AUTO_CLK,
		.timer_num		 = LEDC_TIMER_0,
	};
	
	ledc_timer_config(&ledc_timer);
	
	/* Step 2 : Channel Configuration */
	static ledc_channel_config_t ledc_channel;
	ledc_channel.channel   	= LEDC_CHANNEL_0;
	ledc_channel.duty	   	= 0;
	ledc_channel.gpio_num 	= LED;
	ledc_channel.hpoint	   	= 0; /* Time within the PWM period at which the PWM signal transitions from low to high,This allows you to adjust the phase of the PWM signal by specifying a point (in terms of timer ticks) where the high part of the signal begins. */
	ledc_channel.speed_mode	= LEDC_HIGH_SPEED_MODE;
	ledc_channel.timer_sel	= LEDC_TIMER_0;
	ledc_channel_config(&ledc_channel);
	
	static uint8_t dutyCycle = 0;
	
	while(true){
		ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, dutyCycle);
		ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
		dutyCycle +=50;
		delayms(500);
	}
}