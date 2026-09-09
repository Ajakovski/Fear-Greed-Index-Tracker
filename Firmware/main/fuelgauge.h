#pragma once
#include "esp_err.h"
#include <stding.h>

esp_err_t fuelgauge_init(void);
esp_err_t fuelgauge_read(float *voltage, uint8_t *percent); 