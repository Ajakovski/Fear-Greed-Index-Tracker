#pragma once
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef enum{
    BTN_EVT_NAV_NEXT,
    BTN_EVT_NAV_PREV,
    BTN_EVT_SLEEP_LIGHT, //double click pwr btnnn
    BTN_EVT_SLEEP_DEEP, //single click pwr btnnnn
}button_event_t;

esp_err_t buttons_init(QueueHandle_t out_queue);