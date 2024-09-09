/*
								I2C - Inter-connected circuits
	
			Pins 	 : SCL , SDA
			Features : Two I2C hardware modules (or I2C ports) I2C_NUM_0 and I2C_NUM_1.
					 : The SCL and SDA pins of these instances are not hard-wired to any specific GPIO pin
					 : They are mapped to physical GPIO pins through software configuration.
					 
							
								Steps to Configure I2C
			
			1		 : Configures I2C Structure 
			2		 : Pass That I2C Structure to function i2c_param_config();
			3		 : Make it active by calling i2c_driver_install();
*/

/* libraries */
#include "esp_err.h"
#include "hal/gpio_types.h"
#include "hal/i2c_types.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/i2c.h>
#include <sys/_types.h>
#include <esp_log.h>

static const char *msg = "Hello from Aizaz\n";
#define slaveAddess 0x55
#define timeOut 1000

#define delayms(x) vTaskDelay(x/portTICK_PERIOD_MS)

void app_main(void){
	
	/* Step 1 : Configure Structure */
	i2c_config_t config = {
		.mode				= I2C_MODE_MASTER,
		.scl_io_num			= 22,
		.sda_io_num			= 21,
		.scl_pullup_en  	= GPIO_PULLUP_ENABLE,
		.sda_pullup_en  	= GPIO_PULLUP_ENABLE,
		.master.clk_speed	= 100000, 
	};
	
	/* Step 2 : Pass Structure to function */
	i2c_param_config(I2C_NUM_0, &config);
	
	/* Step 3 : Install or make it active */
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0,0,0));
	
	while(true){
		if (i2c_master_write_to_device(I2C_NUM_0, slaveAddess, (const unsigned char*)msg, strlen(msg), timeOut) == ESP_OK){
			printf("MSG send to slave\n");	
		}
		else{
			printf("MSG not send \n");
		}
		
		delayms(500);
	}
}