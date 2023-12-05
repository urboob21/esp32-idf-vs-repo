
#include "esp_log.h"
#include "tasks_common.h"
#include "mqtt_app.h"
#include "mqtt_client.h"
#include "esp_tls.h"

// Tag used for ESP Serial Console Message
static const char TAG[] = "___MQTT_APP___";
extern const uint8_t mqtt_eclipseprojects_io_pem_start[]   asm("_binary_mqtt_eclipseprojects_io_pem_start");
 extern const uint8_t mqtt_eclipseprojects_io_pem_end[]   asm("_binary_mqtt_eclipseprojects_io_pem_end");
// Client instance
esp_mqtt_client_handle_t client = NULL;

// Wifi connect status
static int g_mqtt_connect_status = MQTT_APP_CONNECT_NONE;

void mqtt_app_task()
{
    while (true)
    {
        if (g_mqtt_connect_status)
        {
            esp_mqtt_client_publish(client, "/topic/test3", "Helllo World", 0, 0, 0);
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

/**
 * MQTT Events handler
 */
static void mqtt_event_handler(void *event_handler_arg,
                               esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    ESP_LOGI(TAG, "Received the MQTT_APP EVENT !");
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        g_mqtt_connect_status = MQTT_APP_CONNECT_SUCCESS;

        msg_id = esp_mqtt_client_subscribe(client, "/topic/test1", 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        msg_id = esp_mqtt_client_subscribe(client, "/topic/test2", 1);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        g_mqtt_connect_status = MQTT_APP_CONNECT_NONE;
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}

/**
 * Start mqtt_app
 */
void mqtt_app_start(void)
{
    ESP_LOGI(TAG, "STARTING MQTT");
    const esp_mqtt_client_config_t mqttConfig = {
        .broker = {
            .address.uri = "mqtts://660f28e90d254c3a969676062a264527.s2.eu.hivemq.cloud:8883",
            .verification.certificate = (const char *)mqtt_eclipseprojects_io_pem_start
        },
        .credentials ={               
            .username= "nphong2103",
            .authentication.password = "210301Phong"          
        }
    };

    client = esp_mqtt_client_init(&mqttConfig);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);

    // Start the MQTT_APP_TAST
    xTaskCreatePinnedToCore(&mqtt_app_task, "MQTT_APP_TASK", MQTT_APP_TASK_STACK_SIZE, NULL, MQTT_APP_TASK_PRIORITY, NULL, MQTT_APP_TASK_CORE_ID);
}