#include "gpio_app.h"
#include "tasks_common.h"
#include <stdio.h>
#include "esp_log.h"
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "rgb_led.h"
#include "wifi_app.h"
#include "lcd2004_app.h"

TaskHandle_t turnOnWarningHandle = NULL;
// Semaphore handle
SemaphoreHandle_t reset_semphore = NULL;
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
            gpio_app_turn_warning(true);
        }

        // process isr
        if (xSemaphoreTake(reset_semphore, portMAX_DELAY) == pdTRUE)
        {

            // Send a message to disconnect Wifi and clear credentials
            wifi_app_send_message(WIFI_APP_MSG_USER_REQUESTED_STA_DISCONNECT);

            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

/**
 * ISR handler for the Wifi reset (BOOT) button
 * @param arg parameter which can be passed to the ISR handler.
 */
void IRAM_ATTR wifi_reset_button_isr_handler(void *arg)
{
    // Notify the button task
    xSemaphoreGiveFromISR(reset_semphore, NULL);
}

/**
 * task ON/OF  warning task - - - NODE DECRE
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

// Turn on off warning
void gpio_app_turn_warning(bool state)
{
    printf("Warning turn %d \n", state);
    gpio_set_level(GPIO_APP_PIN_BUZ, state);
    if (state)
    {
        lcd2004_app_send_message(LCD2004_MSG_ON_WARNING);
    }
    else
    {
        lcd2004_app_send_message(LCD2004_MSG_OFF_WARNING);
    }
}

static void reset_button_config(void)
{
    // Create the binary semaphore
    reset_semphore = xSemaphoreCreateBinary();

    // Configure the button and set the direction
    esp_rom_gpio_pad_select_gpio(GPIO_APP_PIN_RESET_BUTTON);
    gpio_set_direction(GPIO_APP_PIN_RESET_BUTTON, GPIO_MODE_INPUT);

    // Enable interrupt on the negative edge
    gpio_set_intr_type(GPIO_APP_PIN_RESET_BUTTON, GPIO_INTR_NEGEDGE);

    // Install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // Attach the interrupt service routine
    gpio_isr_handler_add(GPIO_APP_PIN_RESET_BUTTON, wifi_reset_button_isr_handler, NULL);
}

/**
 * Starts gpio_app task
 */
void gpio_app_task_start(void)
{
    printf("Start flame & buz \n");
    gpio_app_config();
    reset_button_config();
    xTaskCreatePinnedToCore(&gpio_app_detect_fire_task, "gpio_app_task", GPIO_APP_TASK_STACK_SIZE,
                            NULL, GPIO_APP_TASK_PRIORITY, NULL, GPIO_APP_TASK_CORE_ID);
    // xTaskCreatePinnedToCore(&gpio_app_turn_on_warning_task, "gpio_app_task", GPIO_APP_TASK_STACK_SIZE,
    //                         NULL, GPIO_APP_TASK_PRIORITY, &turnOnWarningHandle, GPIO_APP_TASK_CORE_ID);
}
