#include <stdio.h>
#include "esp_timer.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Create handler */
esp_timer_handle_t esp_timer_handle;

void onCompleate(void *params)
{
    /* As this function will be called after every 50us so we cant use printf() */
    /* we will use gpio to genrate wavefome  */
    static bool onled;
    onled = !onled;
    gpio_set_level(GPIO_NUM_10,onled);
}

void app_main(void)
{
    /* define gpio */
    gpio_set_direction(GPIO_NUM_10,GPIO_MODE_OUTPUT);

    /* fill struct */
    const esp_timer_create_args_t esp_timer_create_args = 
    {
        .name = "esp timer",
        .callback = onCompleate
    };
    /* Pass that struct to timer_create() */
    esp_timer_create(&esp_timer_create_args,&esp_timer_handle);

    /* start esp_timer and period of 50us */
    esp_timer_start_periodic(esp_timer_handle,50);

    while(true)
    {
        esp_timer_dump(stdout); /* dump results to stdout(serial monitor) */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
