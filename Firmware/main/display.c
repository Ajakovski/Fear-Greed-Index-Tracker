#include "display.h"
#include "pins.h"

#include "driver/spi_master.h"
#include "driver/spi_master.h"
#include "driver/ledc.h"
#include "esp_lcd_panel_io.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "lvgl.h"
#include <string.h>
#include <stdio.h>

static const char *TAG = "display";

#define NUM_TABS 2
#define LVGL_BUF_LINES 20
typedef struct{
    uint8_t cmd;
    uint8_t data[8];
    uint8_t len;
    uint16_t delay_ms;
} st7735_cmd_t;

static const st7735_cmd_t st7735_init_seq[] = {
    { 0x01, {0}, 0, 120 },                          // SWRESET
    { 0x11, {0}, 0, 120 },                          // SLPOUT
    { 0xB1, {0x01, 0x2C, 0x2D}, 3, 0 },              // FRMCTR1
    { 0xB2, {0x01, 0x2C, 0x2D}, 3, 0 },              // FRMCTR2
    { 0xB4, {0x07}, 1, 0 },                          // INVCTR
    { 0xC0, {0xA2, 0x02, 0x84}, 3, 0 },              // PWCTR1
    { 0xC1, {0xC5}, 1, 0 },                          // PWCTR2
    { 0xC2, {0x0A, 0x00}, 2, 0 },                    // PWCTR3
    { 0xC5, {0x0E}, 1, 0 },                          // VMCTR1
    { 0x36, {0xC8}, 1, 0 },                          // MADCTL -- see note above
    { 0x3A, {0x05}, 1, 0 },                          // COLMOD, 16-bit RGB565
    { 0x29, {0}, 0, 100 },                           // DISPON
};

static esp_lcd_panel_io_handle_t s_io;
static lv_display_t *s_disp;
static QueueHandle_t s_msg_queue;

static lv_obj_t *s_tabview;
static lv_obj_t *s_change_label[NUM_TABS];
static lv_chart_series_t *s_chart_series[NUM_TABS];
static lv_obj_t *s_chart[NUM_TABS];
static lv_obj_t *s_battery_label;
static int s_current_tab = 0;

static void st7735_set_window(int x0, int y0, int x1,int y1){
    uint8_t caset[4] = {0x00,(uint8_t)x0,0x00,(uint8_t)x1};
    uint8_t raset[4]={0x00,(uint8_t)y0,0x00,(uint8_t)y1};
    esp_lcd_panel_io_tx_param(s_io,0x2A,caset,4);
    esp_lcd_panel_io_tx_param(s_io,0x2B,raset,4);
    esp_lcd_panel_io_tx_param(s_io,0x2C,NULL,0);
}

static void lvgl_flush_cb(lv_display_t *disp,const lv_area_t *area, uint8_t *px_map){
    st7735_set_window(area->x1, area->y1, area->x2, area->y2);
    int w=area->x2 - area->x1+1;
    int h=area->y2 - area->y1+1;
    esp_lcd_panel_io_tx_color(s_io, -1, px_map, (size_t)w*h*c);
    lv_display_flush_ready(disp);
}

static void lvgl_tick_cb(void *arg){
    lv_tick_inc(5);
}

static void panel_init(void){
    spi_bus_config_t buscfg={
        .sclk_io_num=PIN_TFT_SCLK,
        .mosi_io_num=PIN_TFT_MOSI,
        .miso_io_num=-1, //not connected
        .max_transfer_sz=128*LVGL_BUF_LINES*2,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO));

    esp_lcd_panel_io_spi_config_t io_config={
        .cs_gpio_num = PIN_TFT_CS,
        .dc_gpio_num=PIN_TFT_DC,
        .spi_mode=0,
        .pclk_hz=20*1000*1000,
        .trans_queue_depth=10,
        .lcd_cmd_bits=8,
        .lcd_param_bits=8,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST, &io_config, &s_io));

    gpio_config_t rst_cfg ={.pin_bit_mask =1ULL<<PIN_TFT_RST, .mode=GPIO_MODE_OUTPUT};
    gpio_config(&rst_cfg);
    gpio_set_level(PIN_TFT_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(PIN_TFT_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(120));

    for(size_t i=0; i<sizeof(st7735_init_seq)/sizeof(st7735_init_seq[0]);i++){
        const st7735_cmd_t *c= &st7735_init_seq[i];
        esp_lcd_panel_io_tx_param(s_io,c->cmd,c->len?c->data:NULL,c->len);
        if(c->delay_ms) vTaskDelay(pdMS_TO_TICKS(c->delay_ms));
    }
}

static void backlight_init(void){
    ledc_timer_config_t timer_cfg={
        .speed_mode=LEDC_LOW_SPEED_MODE,
        .duty_resolution=LEDC_TIMER_8_BIT,
        .timer_num=LEDC_TIMER_0,
        .timer_sel=LEDC_TIMER_0,
        .duty=255,
    };
    ledc_channel_config(&chan_cfg);
}

void deploy_set_backlight(uint8_t brightness_0_255){
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0,brightness_0_255);
    ledc_update_duty(LEDC_LOW_SPEED_MODE,LEDC_CHANNEL_0);
}

static void build_ui(void){
    s_tabview=lv_tabview_create(lv_screen_active());
    lv_tabview_set_tab_bar_size(s_tabview,0);

    static const char *names[NUM_TABS]={"S&P 500","Nasdaq"};
    for(int i=0;i<NUM_TABS;i++){
        lv_obj_t *tab=lv_tabview_add_tab(s_tabview, names[i]);
        lv_obj_t *symbol_label=lv_label_create(tab);
        lv_label_set_text(symbol_label, names[i]);
        lv_obj_align(symbol_label, LV_ALIGN_TOP_LEFT, 4, 4);

        s_change_label[i] = lv_label_create(tab);
        lv_label_set_text(s_change_label[i],"--");
        lv_obj_align(s_change_label[i], LV_ALIGN_TOP_LEFT,4,22);

        s_chart[i]=lv_chart_create(tab);
        lv_obj_set_size(s_char[i],116,88);
        lv_obj_align(s_chart[i],LV_ALIGN_BOTTOM_NID,0,-4);
        lv_chart_set_type(s_chart[i], LV_CHART_TYPE_LINE);
        lv_chart_set_point_count(s_chart[i], DISPLAY_CHART_POINTS);
        s_chart_series[i] = lv_chart_add_series(s_chart[i],lv_color_black(),LV_CHART_AXIS_PRIMARY_Y);
    }

    s_battery_label=lv_label_create(lv_layer_top());
    lv_label_set_text(s_battery_label, "--%");
    lv_obj_align(s_battery_label, LV_ALIGN_TOP_RIGHT, -4,4);
}

static void handle_msg(const display_msg_t *msg){
    switch(msg->type){
        case DISPLAY_MSG_MARKET_DATA:{
            int i=msg->tab_index;
            if(i<0||i>=NUM_TABS)break;

            char buf[32];
            snprintf(buf,sizeof(buf),"%+.2f%% today%s", msg->market.change_pct_today, msg->stale?" (stale)":"");
            lv_label_set_text(s_change_label[i],buf);

            for(int p=0;p<msg->market.num_points && p<DISPLAY_CHART_POINTS; p++){
                lv_chart_set_value_by_id(s_chart[i],s_chart_series[i],p,(int32_t)(msg->market.close[p]*100));
            }
            lv_chart_refresh(s_chart[i]);
            break;
        }
        case DISPLAY_MSG_BATTERY_PCT:{
            char buf[8];
            snprintf(buf,sizeof(buf),"%d%%", msg->battery_pct);
            lv_label_set_text(s_battery_label, buf);
            break;
        }
        case DISPLAY_MSG_NAV_NEXT:
            s_current_tab=(s_current_tab+1)%NUM_TABS;
            lv_tabview_set_active(s_tabview, s_current_tab, LV_ANIM_ON);
            break;
        case DISPLAY_MSG_NAV_PREV:
            s_current_tab=(s_current_tab-1+NUM_TABS)%NUM_TABS;
            lv_tabview_set_active(s_tabview,s_current_tab, LC_ANIM_ON);
            break;
    }
}

static void display_task(void *arg){
    panel_init();
    backlight_init();
    lv_init();
    static uint8_t lvgl_buf[128*LVGL_BUF_LINES*2];
    s_disp=lv_display_create(128,160);
    lv_display_set_flush_cb(s_disp,lvgl_flush_cb);
    lv_display_set_buffers(s_disp,lvgl_buf,NULL, sizeof(lvgl_buf),LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_color_format(s_disp,LV_COLOR_FORMAT_RGB565);
    const esp_timer_create_args_t tick_args={.callback=&lvgl_tick_cb,.name="lv_tick"};
    esp_timer_hangle_t tick_timer;
    esp_timer_create(&tick_args, &tick_timer);
    esp_timer_start_periodic(tick_timer,5000);
    build_ui();
    display_set_backlight(255);
    ESP_LOGI(TAG,"display task up");
    display_msg_t msg;
    while(1){
        if(xQueueReceive(s_msg_queue, &msg, pdMS_TO_TICKS(50))==pdTRUE){
            handle_msg(&msg);
        }
        lv_timer_handler();
    }
}

void display_post_msg(const display_msg_t *msg){
    if(s_msg_queue){
        xQueueSemd(s_msg_queue,msg,pdMS_TO_TICKS(100));
    }
}

esp_err_t display_init(void){
    s_msg_queue=xQueueCreate(8,sizeof(display_msg_t));
    if(!s_msg_queue)return ESP_ERR_NO_MEM;
    xTaskCreate(display_task,"display",8192,NULL,4,NULL);
    return ESP_OK;
}
