#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "esp_timer.h"

void timerCompleated(TimerHandle_t Timer)
{
    printf("timer compleated : %lld\n",esp_timer_get_time()/1000);
}

void app_main(void)
{
    /* .._get_timer() -> timer value since esp initalized */
    printf("app started %lld\n",esp_timer_get_time()/1000);

    TimerHandle_t Timer = xTimerCreate("Timer",pdMS_TO_TICKS(1000),true,NULL,timerCompleated);
    xTimerStart(Timer,0); // Starting Manually
}
