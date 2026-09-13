#include "wifi_mgr.h"
#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_timer.h"
#include "freertos/event_groups.h"

static const char *TAG = "wifi_mgr";

#define WIFI_CONNECTED_BIT BIT0
#define BACKOFF_MIN_MS 1000
#define BACKOFF_MAX_MS 60000

static EventGroupHandle_t s_wifi_event_group;
static esp_timer_handle_t s_reconnect_timer;
static uint32_t s_backoff_ms=BACKOFF_MIN_MS;
static void reconnect_timer_ch(void *arg){
    ESP_LOGI(TAG, "retrying connection");
    esp_wifi_connect();
}

static void event_handler(void *arg,esp_event_base_t event_base, int32_t event_id, void *event_data){
    if(event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START){
        esp_wifi_connect();
    }else if(event_base==WIFI_EVENT && event_id==WIFI_EVENT_STA_DISCONNECTED){
        xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        ESP_LOGW(TAG, "disconnected, retrying in %lu ms", (unsigned long)s_backoff_ms);

        esp_timer_stop(s_reconnect_timer);
        esp_timer_start_once(s_reconnect_timer, (uint64_t)s_backoff_ms*1000);
        s_backoff_ms=(s_backoff_ms *2> BACKOFF_MAX_MS)? BACKOFF_MAX_MS : s_backoff_ms*2;
    }else if(event_base == IP_EVENT && event_id==IP_EVENT_STA_GOT_IP){
        ip_event_got_ip_t *event=(ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "got ip: "IPSTR, IP2STR(&event->ip_info.ip));
        s_backoff_ms=BACKOFF_MIN_MS;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}

esp_err_t wifi_mgr_init(void){
    s_wifi_event_group =xEventGroupCreate();
    if (s_wifi_event_group==NULL){
        return ESP_ERR_NO_MEM;
    }

    const esp_timer_create_args_t timer_args = {
        .callback = &reconnect_timer_ch,
        .name="wifi_reconnect",
    };

    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &s_reconnect_timer));
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg= WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,&event_handler,NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT,IP_EVENT_STA_GOT_IP, &event_handler,NULL));

    wifi_config_t wifi_config={0};
    strlcpy((char *)wifi_config.sta.ssid,CONFIG_WIFI_SSID, sizeof(wifi_config.sta.ssid));
    strlcpy((char *)wifi_config.sta.password, CONFIG_WIFI_PASSWORD,sizeof(wifi_config.sta.password));
    wifi_config.sta.threshold.authmode=WIFI_AUTH_WPA2_PSK;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_MIN_MODEM));

    return ESP_OK;
}

bool wifi_mgr_wait_connected(TickType_t timeout_ticks){
    EventBits_t bits =xEventGroupWaitBits(s_wifi_event_group, WIFI_CONNECTED_BIT,pdFALSE,pdTRUE, timeout_ticks);
    return (bits &WIFI_CONNECTED_BIT)!=0;
}

bool wifi_mgr_is_connected(void){
    return (xEventGroupGetBits(s_wifi_event_group) &WIFI_CONNECTED_BIT)!=0;
}