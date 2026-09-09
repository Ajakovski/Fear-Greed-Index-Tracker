#pragma once
#include "esp_err.h"
#include <stdint.h>

#define RGB_LED_COUNT 8 //Prone to changes
esp_err_t rgb_led_init(void);
void rgv_led_set_all(uint8_t r, uint8_t g,uint8_t b);
void rgb_led_off(void);