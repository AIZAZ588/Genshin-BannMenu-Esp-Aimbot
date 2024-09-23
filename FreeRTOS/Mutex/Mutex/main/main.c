#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define delayms(x) vTaskDelay(x/portTICK_PERIOD_MS)

SemaphoreHandle_t mutexBus;

void writeToBus(char *msg){
    printf(msg);
}

void tempurature(void* param){
    while(true){
        printf("Reading Tempurature\n");
        if (xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS))
        {
            writeToBus("Tempurature is 100c\n");
            xSemaphoreGive(mutexBus);
        }
        else
        {
            printf("Tempurature Read timeout\n");
        }
        delayms(1000);
    }
}

void humidity(void* param){
    while(true){
        printf("Reading Humidity\n");
        if(xSemaphoreTake(mutexBus,2000/portTICK_PERIOD_MS))
        {
            writeToBus("Humidity is 45%%\n");
            xSemaphoreGive(mutexBus);
        }
        else
        {
            printf("Humidity Read timeout\n");
        }
        delayms(1000);
    }
}

void app_main(void)
{
    mutexBus = xSemaphoreCreateMutex();
    if(mutexBus != NULL)
    {
        xTaskCreate(&tempurature,"tempurature",2048,NULL,2,NULL);
        xTaskCreate(&humidity,"humidity",2048,NULL,2,NULL);
    }
    else
    {
        printf("Failed to create mutex\n");
    }
}
