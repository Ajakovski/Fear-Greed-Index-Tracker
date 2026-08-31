#include "wifi_mgr.h"
#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG="main";

void app_main(void)
{
    esp_err_t ret=nvs_flash_init();
    if(ret==ESP_ERR_NVS_NO_FREE_PAGES || ret==ESP_ERR_NVS_NEW_VERSION_FOUND){
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret=nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(wifi_mgr_init());

    ESP_LOGI(TAG, "waiting for wifi...");
    if(wifi_mgr_wait_connected(pdMS_TO_TICKS(15000))){
        ESP_LOGI(TAG, "wifi connected");
    }else{
        ESP_LOGW(TAG, "still waiting after 15s, it'll keep retrying in the background");
    }

    while (1){
        vTaskDelay(pdMS_TO_TICKS(10000));
        ESP_LOGI(TAG, "alive, wifi connected: %s", wifi_mgr_is_connected()?"yes":"no");
    }
}
