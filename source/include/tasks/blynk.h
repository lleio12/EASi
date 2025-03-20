#pragma once

#include <Arduino.h>
#include "utils/moistureSensor.h"

extern int bomba1;

void iniciarBlynk(UBaseType_t core = 0, uint32_t stackDepth = 7069, UBaseType_t priority = 1);