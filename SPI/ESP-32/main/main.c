/*
    SPI 		 : Serial Peripheral interface
	Features 	 : 4 SPI peripherals are available 
				 : SPI0 SPI1 VSPI HSPI 
				 : SPI0 and SPI1 are reserved for accessing attached flash memory,
				 : you should use SPI2 or SPI3.
				 
				   Steps to Configure SPI 
				   
				   BUS configuration		   
	1			 : Configure SPI Bus Structure     spi_bus_config_t()
	2			 : Pass that Structure to function spi_bus_initialize()
				
				  Device  Registration
	3			 : Configure SPI Device Structure  spi_device_interface_config_t()
	4			 : Pass that Structure to function spi_bus_add_device()
				
*/

/* libraries */
#include "driver/spi_common.h"
#include "esp_err.h"
#include "hal/spi_types.h"
#include "http_parser.h"
#include <stdio.h>
#include <stdbool.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/spi_master.h>
#include <sys/_intsup.h>
#include <string.h>


#define delayms(x) vTaskDelay(x/portTICK_PERIOD_MS)

void sendSPI(spi_device_handle_t *handle , const char* data){
	
	spi_transaction_t t = {
		.tx_buffer = data,
		.length    = strlen(data)*8
	};
	ESP_ERROR_CHECK(spi_device_polling_transmit(*handle,&t));
	
}

void app_main(void){
	
	esp_err_t err;
	
	/* Step 1 configure BUS Structure */
	spi_bus_config_t busConfig = {
		.miso_io_num = 19,
		.mosi_io_num = 23,
		.sclk_io_num = 18,
	};
	
	/* Step 2 pass that structure to function */
	err = spi_bus_initialize(SPI2_HOST, &busConfig, SPI_DMA_CH_AUTO);
	ESP_ERROR_CHECK(err);
	
	
	spi_device_handle_t spi2;
	/* Step 3 Configure SPI device structure */
	spi_device_interface_config_t devcfg = {
		.clock_speed_hz 	= 100000,  // 100khz
		.mode				= 0, 	   // SPI mode 0 (representing a pair of (CPOL, CPHA) configuration)
		.spics_io_num		= 5,
		.queue_size			= 1,
		.pre_cb				= NULL, // call back
		.post_cb			= NULL,
	};
	
	err = spi_bus_add_device(SPI2_HOST, &devcfg,&spi2);
	
	ESP_ERROR_CHECK(err);
	
	while(true){
		sendSPI(&spi2, "A\n");
		delayms(500);
	}
}
