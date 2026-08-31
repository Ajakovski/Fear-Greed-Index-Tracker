idf_component_register(SRCS "desk_tracker/wifi_mgr.c" "main.c"
                    INCLUDE_DIRS "." "desk_tracker"
                    REQUIRES nvs_flash esp_wifi esp_event esp_netif esp_timer)
