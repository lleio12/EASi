#pragma once

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID     "TMPL5i2z9CRPw"
#define BLYNK_TEMPLATE_NAME   "EASI"
#define BLYNK_AUTH_TOKEN      "Iq2gtah4aNJB_ZyzkLsuoTblYGN4kIFu"

#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

extern int bomba1;

void iniciarBlynk(UBaseType_t core = 0, uint32_t stackDepth = 2069, UBaseType_t priority = 1);