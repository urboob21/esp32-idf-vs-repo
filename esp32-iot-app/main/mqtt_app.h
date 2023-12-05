#ifndef MAIN_MQTT_AP_H
#define MAIN_MQTT_AP_H

#define MQTT_APP_BROKER_URI "mqtts://660f28e90d254c3a969676062a264527.s2.eu.hivemq.cloud:8883"
#define MQTT_APP_USER "nphong2103"
#define MQTT_APP_PASSWORD "210301Phong"
#define MQTT_APP_TOPIC_SUB "topic/request"
#define MQTT_APP_TOPIC_PUB "topic/reply"

/**
 * Connection status for Wifi
 */
typedef enum mqtt_app_connect_status
{
	MQTT_APP_CONNECT_NONE = 0,
	MQTT_APP_CONNECT_SUCCESS
} mqtt_app_connect_status_e;

/**
 * Message IDs for the MQTT application t
 */
typedef enum
{
	MQTT_APP_MSG_START = 0,
	MQTT_APP_MSG_CONNECTED,
	MQTT_APP_MSG_DISCONNECTED,
	MQTT_APP_MSG_SUBSCRIBED,
	MQTT_APP_MSG_PUBLISHED,

} mqtt_app_message_id_e;

/**
 * Message struct  for the MQTT app
 */
typedef struct
{
	mqtt_app_message_id_e msgId;
} mqtt_app_message_t;

/**
 * Sends message function
 */
BaseType_t mqtt_app_send_message(mqtt_app_message_id_e msg);

/**
 * Start mqtt client when wifi connected station mode
 */
void mqtt_app_start();

/**
 * Stop mqtt client when wifi disconnected station mode
 */
void mqtt_app_stop();

#endif