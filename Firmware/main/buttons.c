#include "buttons.h"
#include "pins.h"

#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "freertos/task.h"

static const char *TAG="buttons";

#define DEBOUNCE_US 30000 //Buttons have small debounce noise glitching
#define DOUBLE_CLICK_US 350000
typedef struct{
    gpio_num_t pin;
    int64_t timestamp_us;
}isr_edge_t;

static QueueHandle_t s_isr_queue;
static QueueHandle_t s_out_queue;
static int64_t s_last_edge_us[GPIO_NUM_MAX];

static void IRAM_ATTR gpio_isr_handler(void *arg){
    isr_edge_t edge={
        .pin=(gpio_num_t)(intptr_t)arg,
        .timestamp_us=esp_timer_get_time(),
    };
    BaseType_t woken =pdFALSE;
    xQueueSendFromISR(s_isr_queue,&edge,&woken);
    if (woken)portYIELD_FROM_ISR();
}

static void configure_button_pin(gpio_num_t pin){
    gpio_config_t cfg={
        .pin_bit_mask=1ULL<<pin,
        .mode=GPIO_MODE_INPUT,
        .pull_up_en=GPIO_PULLUP_ENABLE,
        .intr_type=GPIO_INTR_NEGEDGE,
    };
    gpio_config(&cfg);
    gpio_isr_handler_add(pin,gpio_isr_handler,(void *)(intptr_t)pin);
}

static void button_task(void *arg){
    isr_edge_t edge;
    int power_click_count=0;
    int64_t power_first_click_us=0;
    while(1){
        TickType_t wait_ticks=portMAX_DELAY;
        if(power_click_count==1){
            int64_t elapsed=esp_timer_get_time()-power_first_click_us;
            int64_t remaining_us=DOUBLE_CLICK_US-elapsed;
            if(remaining_us<0)remaining_us=0;
            wait_ticks=pdMS_TO_TICKS(remaining_us/1000+1);
        }
        if(xQueueReceive(s_isr_queue, &edge,wait_ticks)==pdTRUE){
            if(edge.timestamp_us-s_last_edge_us[edge.pin]<DEBOUNCE_US){
                continue;
            }
            s_last_edge_us[edge.pin]=edge.timestamp_us;
            if(edge.pin==PIN_BTN_NAV1){
                button_event_t evt=BTN_EVT_NAV_NEXT;
                xQueueSend(s_out_queue, &evt,0);
            }else if (edge.pin==PIN_BTN_NAV2){
                button_event_t evt=BTN_EVT_NAV_PREV;
                xQueueSend(s_out_queue,&evt,0);
            }else if(edge.pin==PIN_BTN_POWER){
                if(power_clicl_count==0){
                    power_click_count=1;
                    power_first_click_us=edge.timestamp_us;
                }else{
                    power_click_count=0;
                    button_event_t evt=BTN_EVT_SLEEP_LIGHT;
                    xQueueSend(s_out_queue, &evt,0);
                    ESP_LOGI(TAG,"power: double click");
                }
            }
        }else if(power_click_count==1){
            power_click_count=0;
            button_event_t evt=BTN_EVT_SLEEP_DEEP;
            xQueueSend(s_out_queue, &evt,0);
            ESP_LOGI(TAG, "power: single click");
        }
    }
}
esp_err_t buttons_init(QueueHandle_t out_queue){
    s_out_queue=out_queue;
    s_isr_queue=xQueueCreate(8,sizeof(isr_edge_t));
    if(!s_isr_queue)return ESP_ERR_NO_MEM;

    gpio_install_isr_service(0);
    configure_button_pin((gpio_num_t)PIN_BTN_POWER);
    configure_button_pin((gpio_num_t)PIN_BTN_NAV1);
    configure_button_pin((gpio_num_t)PIN_BTN_NAV2);

    xTaskCreate(button_task,"buttons",3072,NULL,10,NULL);
    return ESP_OK;
}