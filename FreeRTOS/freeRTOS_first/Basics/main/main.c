#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define delayms(x) vTaskDelay(x/portTICK_PERIOD_MS)

void task1(void){
    while (true)
    {
       printf("Reading Tempurature\n");
       delayms(2000);
    }
    
}

void task2(void){
    while(true)
    {
        printf("Reading Humidity\n");
        delayms(1000);
    }
}

void app_main(void)
{
    xTaskCreate(&task1,"Tempurature Reading",2048,NULL,2,NULL);
    xTaskCreate(&task2,"Humidity Reading",2028,NULL,2,NULL);

    /* 
        Above Tasks will be running on same core
        To use another Core use below sentex
    */
//    xTaskCreatePinnedToCore(&task2,"Humidity Reading",2028,NULL,2,NULL,1);
//                                                                       ^ means core 1
}
