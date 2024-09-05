/*
	Timer 0 : 64 bit
			: default frequency is 80Mhz
*/

/* libraries */
#include "driver/timer_types_legacy.h"
#include "esp_attr.h"
#include "esp_intr_alloc.h"
#include "esp_rom_gpio.h"
#include "hal/gpio_types.h"
#include <stdio.h>
#include <driver/gpio.h>
#include <driver/timer.h>
#include <driver/gptimer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdbool.h>
#include <esp_log.h>

#define LED GPIO_NUM_27
#define delay_ms(x) vTaskDelay(x/portTICK_PERIOD_MS)

static bool toggle = true;


void IRAM_ATTR timer_isr_handler(void* arg){
	
	/* clear timer flag */
	timer_group_clr_intr_status_in_isr(TIMER_GROUP_0, TIMER_0);
	
	/* Re-enable alarm  */
	timer_group_enable_alarm_in_isr(TIMER_GROUP_0, TIMER_0);
	
	gpio_set_level(LED,toggle);
	toggle =! toggle;
	
}

void init_timer(void){
	
	/* Timer Configuration structure */
	timer_config_t config = {
		.divider  		= 80, 					/* clock divider 80/80 = 1Mhz frequency */
		.alarm_en 		= TIMER_ALARM_EN, 		/* Enable Alarm 						*/
		.auto_reload 	= TIMER_AUTORELOAD_EN,  /* Auto reload enable 					*/
		.counter_dir    = TIMER_COUNT_UP,		/* Up Counter 							*/
		.counter_en     = TIMER_PAUSE,			/* Start in pause mode 					*/
	};
	
	/* Initialize timer */
	timer_init(TIMER_GROUP_0,TIMER_0,&config);
	
	/* Clear timer register, set counter value to 0 */
	timer_set_counter_value(TIMER_GROUP_0,TIMER_0,0x0ULL);
	
	/* Configure alarm value (1 second  = 1,000,000 ticks at 1 MHz) */
	timer_set_alarm_value(TIMER_GROUP_0, TIMER_0, 1000000);
	
	/* Enable Interrupt and register ISR */
	timer_enable_intr(TIMER_GROUP_0, TIMER_0);
	timer_isr_register(TIMER_GROUP_0, TIMER_0, timer_isr_handler, NULL, ESP_INTR_FLAG_IRAM, NULL);
	
	/* Start timer 0 */
	timer_start(TIMER_GROUP_0,TIMER_0);
}

void app_main(void){
	
	esp_rom_gpio_pad_select_gpio(LED);
	gpio_set_direction(LED,GPIO_MODE_OUTPUT);
	init_timer();
	
	while(true){
		
	ESP_LOGD("LED : ","%s", (toggle == true) ? "ON" : "OFF");
	delay_ms(100);
	}
}