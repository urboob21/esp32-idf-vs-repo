/*
 * rgb_led.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Phong Nguyen
 */

#ifndef MAIN_RGB_LED_H_
#define MAIN_RGB_LED_H_
// RGB GPIOs LED
#define RGB_GPIO_LED_BLUE		21
#define RGB_GPIO_LED_GREEN		22
#define RGB_GPIO_LED_RED		23

// RGB LED Channels
#define RGB_CHANNEL_NUM			3

// RGB LED configuration
typedef struct {
	int channel;
	int gpio;
	int mode;
	int timer_index;
} ledc_info_t;

/**
 * Color to indicate
 */
void rgb_led_test_started();

/**
 * User R-G-B color
 */
void rgb_led_display(uint8_t r,uint8_t g,uint8_t b);

/**
 * Color to indicate WiFi application has started.
 */
void rgb_led_wifi_app_started(void);

/**
 * Color to indicate HTTP server has started.
 */
void rgb_led_http_server_started(void);

/**
 * Color to indicate that the ESP32 is connected to an access point.
 */
void rgb_led_wifi_connected(void);
#endif /* MAIN_RGB_LED_H_ */
