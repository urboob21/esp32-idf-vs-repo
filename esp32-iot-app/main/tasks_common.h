/*
 * tasks_common.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Phong Nguyen
 */

#ifndef MAIN_TASKS_COMMON_H_
#define MAIN_TASKS_COMMON_H_

// WIFI task
#define WIFI_APP_TASK_STACK_SIZE 4069
#define WIFI_APP_TASK_PRIORITY 5
#define WIFI_APP_TASK_CORE_ID 0

// HTTP Server task (process from server ??)
#define HTTP_SERVER_TASK_STACK_SIZE 8192
#define HTTP_SERVER_TASK_PRIORITY 4
#define HTTP_SERVER_TASK_CORE_ID 0

// HTTP Server Monitor task (freeRTOS task)
#define HTTP_SERVER_MONITOR_STACK_SIZE 4096
#define HTTP_SERVER_MONITOR_PRIORITY 3
#define HTTP_SERVER_MONITOR_CORE_ID 0

// DHT 22 sensor task
#define DHT22_TASK_STACK_SIZE 4096
#define DHT22_TASK_PRIORITY 5
#define DHT22_TASK_CORE_ID 1

// GPIO app task
#define GPIO_APP_TASK_STACK_SIZE 1024
#define GPIO_APP_TASK_PRIORITY 5
#define GPIO_APP_TASK_CORE_ID 1


// MQTT App task
#define MQTT_APP_TASK_STACK_SIZE 5120
#define MQTT_APP_TASK_PRIORITY 6
#define MQTT_APP_TASK_CORE_ID 1

#endif /* MAIN_TASKS_COMMON_H_ */
