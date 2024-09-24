#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define delayms(x)  vTaskDelay(x/portTICK_PERIOD_MS)

SemaphoreHandle_t binarySema = NULL;

void task1(void* param){
    while(true){
        // if recived data than give semaphore
        printf("data recived\n");
        xSemaphoreGive(binarySema);
        delayms(3000);
    }

}
void task2(void* param){
    while(true){
        // if semaphore is avalible than do something with that data
        xSemaphoreTake(binarySema,portMAX_DELAY);
        printf("Action on data\n");

    }
}

void app_main(void)
{
    binarySema = xSemaphoreCreateBinary();
    if(binarySema != NULL){
        xTaskCreate(&task1,"give",2048,NULL,1,NULL);
        xTaskCreate(&task2,"taske",2048,NULL,1,NULL);
    }
}
