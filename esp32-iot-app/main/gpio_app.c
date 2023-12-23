#include "gpio_app.h"
#include "tasks_common.h"
#include <stdio.h>
#include "esp_log.h"
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rgb_led.h"
TaskHandle_t turnOnWarningHandle = NULL;

/**
 * gpio_app config
 */
static void gpio_app_config()
{
    // Flame sensor config
    gpio_set_direction(GPIO_APP_PIN_FLAME, GPIO_MODE_INPUT);

    // Buzz warning config
    gpio_set_direction(GPIO_APP_PIN_BUZ, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_APP_PIN_BUZ, 0);
}

/**
 * gpio_app task
 */
static void gpio_app_detect_fire_task()
{
    for (;;)
    {
        if (!gpio_get_level(GPIO_APP_PIN_FLAME) == 0)
        {
            printf("Flame dected => the fire is detected \n");
            // vTaskResume(turnOnWarningHandle);
            gpio_set_level(GPIO_APP_PIN_BUZ, 1);
            rgb_led_display(RGB_COLOR_RED);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

/**
 * task ON/OF  warning task
 */
void gpio_app_turn_warning_task(bool state)
{
    vTaskSuspend(NULL);
    for (;;)
    {
        gpio_set_level(GPIO_APP_PIN_BUZ, state);
        vTaskSuspend(turnOnWarningHandle);
    }
}

void gpio_app_turn_warning(bool state)
{
    printf("Warning turn %d \n", state);
    gpio_set_level(GPIO_APP_PIN_BUZ, state);

    if (state)
    {
        rgb_led_display(RGB_COLOR_RED);
    }
    else if (!state)
    {
        rgb_led_display(RGB_COLOR_GREEN);
    }
}

/**
 * Starts gpio_app task
 */
void gpio_app_task_start(void)
{
    printf("Start flame & buz \n");
    gpio_app_config();
    xTaskCreatePinnedToCore(&gpio_app_detect_fire_task, "gpio_app_task", GPIO_APP_TASK_STACK_SIZE,
                            NULL, GPIO_APP_TASK_PRIORITY, NULL, GPIO_APP_TASK_CORE_ID);
    // xTaskCreatePinnedToCore(&gpio_app_turn_on_warning_task, "gpio_app_task", GPIO_APP_TASK_STACK_SIZE,
    //                         NULL, GPIO_APP_TASK_PRIORITY, &turnOnWarningHandle, GPIO_APP_TASK_CORE_ID);
}