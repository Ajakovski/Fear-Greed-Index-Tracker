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