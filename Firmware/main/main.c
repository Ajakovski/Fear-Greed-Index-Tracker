#include "wifi_mgr.h"
#include "buttons.h"
#include "data_fetch.h"
#include "display.h"
#include "fuelgauge.h"
#include "rgb_led.h"
#include "pins.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_wifi.h"
#include "driver/rtc_io.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

static const char *TAG="main";
static QueueHandle_t s_btn_queue;

static void enter_deep_sleep(void){
    ESP_LOGI(TAG,"entering deep sleep");
    rgb_led_off();
    rtc_gpio_pullup_en(PIN_BTN_POWER);
    rtc_gpio_pulldown_dis(PIN_BTN_POWER);
    esp_sleep_enable_ext0_wakeup(PIN_BTN_POWER,0);
    esp_deep_sleep_start();
}

static void enter_light_sleep(void){
    ESP_LOGI((TAG,"entering light sleep"));
    display_set_backlight(0);
    rgb_led_off();
    esp_wifi_stop();

    gpio_wakeup_enable(PIN_BTN_POWER, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();
    esp_light_sleep_start();
    esp_wifi_start();
    display_set_backlight(255);
    display_refresh_led();
    ESP_LOGI(TAG,"woke from light sleep"); 
}

static void fuelgauge_task(void *arg){
    fuelgauge_init();
    while(1){
        float voltage;
        uint8_t percent;
        if(fuelgauge_read(&voltage,&percent)==ESP_OK){
            display_msg_t msg={.type=DISPLAY_MSG_BATTERY_PCT, .battery_pct=percent};
            display_post_msg(&msg);
        }
        vTaskDelay(pdMS_TO_TICKS(60000));}}

void main(void){
    esp_err_t ret=nvs_flash_init();
    if(ret==ESP_ERR_NVS_NO_FREE_PAGES|| ret==ESP_ERR_NVS_NEW_VERSION_FOUND){
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret=nvs_flash_init();       
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(wifi_mgr_init());
    ESP_ERROR_CHECK(display_init());
    ESP_ERROR_CHECK(data_fetch_init());
    xTaskCreate(fuelgauge_task,"fuelgauge",3072,NULL,3,NULL);
    s_btn_queue=xQueueCreate(4,sizeof(button_event_t));
    ESP_ERROR_CHECK(buttons_init(s_btn_queue));
    ESP_LOGI(TAG,"waiting for wifi...");
    if(wifi_mgr_wait_connected(pdMS_TO_TICKS(15000))){
        ESP_LOGI(TAG,"wifi connected");
    }else{
        ESP_LOGW(TAG,"still waiting, it'll keep retrying in the background");
    }
    button_event_t evt;
    while(1){
        if(xQueueReceive(s_btn_queue,&evt,portMAX_DELAY)==pdTRUE){
            switch(evt){
                case BTN_EVT_NAV_NEXT:{
                    display_msg_t msg={.type=DISPLAY_MSG_NAV_NEXT};
                    display_post_msg(&msg);
                    break;
                }
                case BTN_EVT_NAV_PREV:{
                    display_msg_t msg={.type=DISPLAY_MSG_NAV_PREV};
                    display_post_msg(&msg);
                    break;
                }
                case BTN_EVT_SLEEP_DEEP;
                    enter_deep_sleep();break;
                case BTN_EVT_SLEEP_LIGHT;
                enter_light_sleep();
                break;
            }
        }
    }
}
