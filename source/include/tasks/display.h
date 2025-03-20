#pragma once
#include <Arduino.h>
#include "utils/moistureSensor.h"

void iniciarDisplay(UBaseType_t core = 0, uint32_t stackDepth = 8000, UBaseType_t priority = 0);
void iniciarBotao(UBaseType_t core = 0, uint32_t stackDepth = 8000, UBaseType_t priority = 0);