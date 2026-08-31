#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#define DISPLAY_CHART_POINTS 7

typedef struct{
    char symbol[8];
    float change_pct_today;
    float closes[DISPLAY_CHART_POINTS];
    int num_points;
} market_series_t;

typedef enum{
    DISPLAY_MSG_MARKET_DATA,
    DDISPLAY_MSG_BATTERY_PCT,
    DISPLAY_MSG_NAV_NEXT,
    DISPLAY_MSG_NAV_PREV,
} display_msg_type_t;

typedef struct{
    display_msg_type_t type;
    int tab_index;
    market_series_t market;
    uint8_t battery_pct;
    bool stale;   
} display_msg_t;

esp_err_t display_init(void);
void display_post_msg(const display_msg_t *msg);
void display_set_backlight(uint8_t brightness_0_225);