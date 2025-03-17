#pragma once
#include "blynkConfig.h"  // Include Blynk definitions first
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

extern BlynkWifi Blynk;

void iniciarBlynkTask(UBaseType_t core = 0, uint32_t stackDepth = 4096, UBaseType_t priority = 1);