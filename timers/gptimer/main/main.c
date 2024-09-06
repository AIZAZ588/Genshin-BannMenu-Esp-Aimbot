/*
	GPTIMER : General purpose timers
			: high level API provided by ESP-IDF
			: Simplifies the use of traditional timers (timer0 to timer3)
			: flexible and use friendly
			: precise
*/

/* libraries */
#include "driver/gptimer_types.h"
#include "esp_rom_gpio.h"
#include "hal/timer_types.h"
#include "soc/clk_tree_defs.h"
#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <driver/gptimer.h>


#define LED GPIO_NUM_27
#define delayms(x) vTaskDelay(x/portTICK_PERIOD_MS)

bool IRAM_ATTR on_alarm_fn(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx){
	static bool ON = true;
	gpio_set_level(LED, ON);
	ON = !ON;
	return true;
} 

void app_main(void){
	
	/* LED GPIO configuration  */
	esp_rom_gpio_pad_select_gpio(LED);
	gpio_reset_pin(LED);
	gpio_set_direction(LED,GPIO_MODE_OUTPUT);
	
	/* GPTimer Configuration   */
	gptimer_handle_t gptimer = NULL;
	gptimer_config_t timer_config = {
		.clk_src 		= GPTIMER_CLK_SRC_DEFAULT,
		.direction  	= GPTIMER_COUNT_UP,
		.resolution_hz  = 1000000,           /* 1Mhz (1 tick = 1 microsecond) */
	};
	
	gptimer_new_timer(&timer_config , &gptimer);
	
	/* Alarm Configuration 	   */
	gptimer_alarm_config_t alarm_config = {
		.alarm_count   					= 500000,  /* 500ms */
		.reload_count  					= 0,
		.flags.auto_reload_on_alarm 	= true,
	};
	gptimer_set_alarm_action(gptimer, &alarm_config);
	
	
	/* Callback register 	   */
	gptimer_event_callbacks_t callback = {
		.on_alarm = on_alarm_fn,
	};
	gptimer_register_event_callbacks(gptimer,&callback,NULL);
	
	/* Enable and start timer */
	gptimer_enable(gptimer);
	gptimer_start(gptimer);
	
	while(true){
		delayms(100);
	}
}