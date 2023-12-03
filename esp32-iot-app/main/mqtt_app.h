#ifndef MAIN_MQTT_AP_H
#define MAIN_MQTT_AP_H

#define MQTT_APP_BROKER_URI "mqtt://660f28e90d254c3a969676062a264527.s2.eu.hivemq.cloud:8883"
#define MQTT_APP_USER		"nphong2103"
#define MQTT_APP_PASSWORD	"210301Phong"
/**
 * Connection status for Wifi
 */
typedef enum mqtt_app_connect_status {
	MQTT_APP_CONNECT_NONE = 0,
	MQTT_APP_CONNECT_SUCCESS
} mqtt_app_connect_status_e;

/**
 * Start mqtt client when wifi connected
*/
void mqtt_app_start();


#endif 