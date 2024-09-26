#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// Create handler
QueueHandle_t QueueNum = NULL;

void sender(void *param)
{
    int count = 0;
    while (true)
    {
        count++;
        if (xQueueSend(QueueNum, &count, 1000 / portTICK_PERIOD_MS))
        {
            printf("Data send to Queue\n");
        }
        else
        {
            printf("Faild to send Data to Queue\n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void reciver(void *param)
{
    int recivedCount;
    while (true)
    {
        if (xQueueReceive(QueueNum, &recivedCount, 3000 / portTICK_PERIOD_MS))
        {
            printf("Recived Count : %d\n", recivedCount);
        }
        else
        {
            printf("Time out Failed to recive Queue\n");
        }
    }
}

void app_main(void)
{
    QueueNum = xQueueCreate(3, sizeof(int));
    if (QueueNum != NULL)
    {
        xTaskCreate(&sender, "Sender", 2048, NULL, 1, NULL);
        xTaskCreate(&reciver, "Reciver", 2048, NULL, 1, NULL);
    }
}
