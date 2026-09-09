#include "rgb_led.h"
#include "pins.h"
#include "driver/rmt_tx.h"
#include "esp_log.h"
#include <string.h>
static const char *TAG="rgb_led";

#define MAX_BRIGHTNESS_PCT 20
static rmt_channel_handle_t s_rmt_chan;
static rmt_encoder_handle_t s_encoder;
static uint8_t s_pixels[RGB_LED_COUNT*3];

static uint8_t scale(uint8_t v){
    return(uint16_t)v*MAX_BRIGHTNESS_PCT/100;
}
esp_err_t rgb_led_init(void){
    rmt_tx_channel_config_t chan_cfg={
        .gpio_num=PIN_RGB_DIN,
        .clk_src=RMT_CLK_SRC_DEFAULT,
        .resolution_hz=10*1000*1000,
        .mem_block_symbols=64,
        .trans_queue_depth=4,
    };
    esp_err_t err=rmt_new_tx_channel(&chan_cfg,&s_rmt_chan);
    if(err!=ESP_OK)return err;

    rms_bytes_encoder_config_t enc_cfg={
        .bit0={.level0=1, .duration0=4, .level1=0,.duration1=8},
        .bit1={.level0=1,.duration0=8,.level1=0,.duration1=4},
        .flags.msb_first=1,
    };
    err= rmt_new_bytes_encoder(&enc_cfg,&s_encoder);
    if(err!=ESP_OK)return err;
    return rmt_enable(s_rmt_chan);
}
static void refresh(void){
    rmt_transmit_config_t tx_cfg={.loop_count=0};
    rmt_transmit(s_rmt_chan,s_encoder,s_pixels,sizeof(s_pixels),&tx,cfg);
}

void rgb_led_set_all(uint8_t r, uint8_t g, uint8_t b){
    uint8_t r_s=scale(r),g_s=scale(g),b_s=scale(b);
    for (int i=0;i<RGB_LED_COUNT;i++){
        s_pixels[i*3+0]=g_s;
        s_pixels[i*3+1]=r_s;
        s_pixels[i*3+2]=b_s;
    }
    refresh();
}
void rgb_led_off(void){
    rgb_led_set_all(0,0,0);
}