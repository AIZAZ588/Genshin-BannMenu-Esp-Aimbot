#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


#define delayms(x) vTaskDelay(x / portTICK_PERIOD_MS)
static TaskHandle_t reciverHandler = NULL;

void sender(void *param)
{
    while (true)
    {
        xTaskNotifyGive(reciverHandler);
        delayms(2000);
    }
}
void reciver(void *param)
{
    while (true)
    {
        ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
        printf("Notification recived!\n");
    }
}

void app_main(void)
{
    xTaskCreate(&reciver, "reciver", 2048, NULL, 2, &reciverHandler);
    xTaskCreate(&sender, "Sender", 2048, NULL, 2, NULL);
}