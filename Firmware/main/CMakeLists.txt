idf_component_register(SRCS "desk_tracker/wifi_mgr.c" "main.c" "buttons.c" "fuelgauge.c" "data_fetch.c" "display.c" "rgb_led.c"
                    INCLUDE_DIRS "." "desk_tracker"
                    REQUIRES nvs_flash esp_wifi esp_event esp_netif esp_timer 
                    esp_http_client esp_hw_support driver esp_lcd json esp_timer)
