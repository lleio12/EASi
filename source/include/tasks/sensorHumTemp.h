#pragma once
#include <Arduino.h>

esp_err_t DHT11_Init(gpio_num_t gpio_num);
esp_err_t DHT11_Read(float *humidity, float *temperature);


void iniciarHumTemp(UBaseType_t core = 0, uint32_t stackDepth = 1024, UBaseType_t priority = 0);
