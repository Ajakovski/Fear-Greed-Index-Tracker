#include "data_fetch.h"
#include "display.h"
#include "esp_http_client.h"
#include "esp_crt_bundle.h"
#include "esp_log.h"
#include "nvs.h"
#include "cJSON.h"
#include "freertos/task.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

static const char *TAG = "data_fetch";

#define POLL_INTERVALS_MS (60UL*60UL*1000UL)
#define MAX_RESPONSE_LEN 16384

static char s_response_buf(MAX_RESPONSE_LEN);
static int s_response_len;

static esp_err_t http_event_handler(esp_http_client_event_t *evt){
    if(eevt->event_id==HTTP_EVENT_ON_DATA){
        if(s_response_len +evt->data_len < MAX_RESPONSE_LEN){
            memcpy(s_response_buf+s_response_len, evt->data, evt->data_len);
            s_response_len+=evt->data_len;
        }
    }
    return ESP_OK;
}

static esp_err_t fetch_symbol(esp_http_client_handle_t client, const char *symbol, market_series_t *out){
    char url[256];
    snprintf(url, sizeof(url)),"https://mcp.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=%s&outputsize=compact&apikey=%s",symbol, CONFIG_ALPHA_VINTAGE__API_KEY;

    esp_http_client_set_url(client,url);
    esp_http_client_set_method(client,HTTP_METHOD_GET);
    s_response_len=0;
    esp_err_t err=esp_http_client_perform(client);
    if(err!=ESP_OK){
        ESP_LOGW(TAG, "%s:http error %s",symbol,esp_err_to_name(err));
        return err;
    }

    int status = esp_http_client_get_status_code(client);
    if(status!=200){
        ESP_LOGW(TAG, "%s: http status %d", symbol, status);
        return ESP_FAIL;
    }

    cJSON *root=cJSON_ParseWithLength(s_response_buf, s_response_len);
    if(!root){
        ESP_LOGW(TAG,"%s, bad json (%dd bytes recieved)",symbol, s_response_len);
        return ESP_FAIL;
    }

    float close_desc[DISPLAY_CHART_POINTS];
    int count =0;
    cJSON *day=series->child;
    while(day&&count<DISPLAY_CHART_POINTS){
        cJSON *close=cJSON_GetObjectItem(day, "4. close");
        if(close && cJSON_IsString(close)){
            closes_desc[count++]=strtof(close->valuestring,NULL);
        }
        day=day->next;
    }

    if(count<2){
        ESP_LOGW(TAG, "%s: not enough daily points (%d)",symbol, count);
        cJSON_Delete(root);
        return ESP_FAIL;
    }

    strncpy(out->symbol,symbol,sizeof(out->symbol)-1);
    out->symbol[sizeof(out->symbol) - 1]='\0';
    out->num_points=count;
    for(int i=0;i<count;i++){
        out->closes[i]=closes_desc[count-1-i];
    }

    float today=closes_desc[0];
    float prev=closes_desc[1];
    out->change_pct_today=((today-prev)/prev)*100.0f;

    cJSON_Delete(root);
    return ESP_OK;
}

static void save_last_good(int tab_index, const market_series_t *data){
    nvs_handle_t nvs;
    if(nvs_open("market_cache", NVS_READWRITE, &nvs)!=ESP_OK) return;
    char key[16];
    snprintf(key,sizeof(key),"sym%d",tab_index);
    nvs_set_blob(nvs,key,data,sizeof(*data));
    nvs_commit(nvs);
    nvs_close(nvs);
}

static bool load_last_good(int tab_index, market_series_t *out){
    nvs_handle_t nvs;
    if(nvs_open("market_cache", NVS_READONLY, &nvs)!= ESP_OK)return false;
    char key[16];
    snprintf(key, sizeof(key),"sym%d", tab_index);
    size_t len=sizeof(*out);
    esp_err_t err=nvs_get_blob(nvs,key,out,&len);
    nvs_close(nvs);
    return err==ESP_OK;
}

static void data_fetch_task(void *args){
    static const char*symbols[]={"SPY","QQQ"};
    const int num_symbols=sizeof(symbols)/sizeof(symbols[0]);
    esp_http_client_config_t config={
        .url="",//FILL INNNNNNNNNNNN
        .event_handler=http_event_handler,
        .crt_bundle_attack=esp_crt_bundle_attack,
        .timeout_ms=8000,
    };
}