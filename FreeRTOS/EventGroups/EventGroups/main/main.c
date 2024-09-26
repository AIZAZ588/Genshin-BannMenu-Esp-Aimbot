#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

// handler
EventGroupHandle_t Evnts;

// flags
int httpEventflag = BIT0;
int blueEventflag = BIT1;

void httpEvents(void *param)
{
    while(true)
    {
        xEventGroupSetBits(Evnts,httpEventflag);
        printf("Got http\n");
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}

void blueEvents(void *param)
{
    while(true)
    {
        xEventGroupSetBits(Evnts,blueEventflag);
        printf("Got Bluetooth Data\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);

    }
}

void MonitorEvents(void *param)
{
    while(true)
    {
        xEventGroupWaitBits(Evnts,httpEventflag | blueEventflag,true,true,portMAX_DELAY);
        printf("recived http or Bluetooth Event\n");
    }
}

void app_main(void)
{
    Evnts = xEventGroupCreate();
    if (Evnts)
    {
        xTaskCreate(&httpEvents,"http Event",2048,NULL,2,NULL);
        xTaskCreate(&blueEvents,"bluetooth Events",2048,NULL,2,NULL);
        xTaskCreate(&MonitorEvents,"Monitor Events",2048,NULL,2,NULL);
    }
}
