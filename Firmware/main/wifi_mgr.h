#pragma once

#include <stdbool.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"

esp_err_t wifi_mgr_init(void);
bool wifi_mgr_wait_connected(TickType_t timeout_ticks);
bool wifi_mgr_is_connected(void);