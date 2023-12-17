#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_event.h"
#include "rgb_led.h"
#include "wifi_app.h"
#include "nvs_flash.h"
#include "dht22.h"
#include "mqtt_app.h"
#include "gpio_app.h"
// GIT CHECK COMMIT
void wifi_app_connected_events()
{
	// to do some thing
	mqtt_app_start();

}

/**
 * Entry point
*/
void app_main(void)
{
	// Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	// Start flame + warning sensor
	 gpio_app_task_start();
	
	// Start Wifi
	wifi_app_start();

	// Start DHT
	DHT22_task_start();

	// Register the funtion callback MQTT when connected successfully wifi host
	wifi_app_set_callback(*wifi_app_connected_events);
}