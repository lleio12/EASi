#pragma once
#include <DHT.h>

esp_err_t DHT11_Init(gpio_num_t gpio_num);
esp_err_t DHT11_Read(float *humidade, float *temperatura);

extern float humidade, temperatura;

void iniciarHumTemp(UBaseType_t core = 0, uint32_t stackDepth = 4000, UBaseType_t priority = 0);
