#pragma once

#include <Arduino.h>

extern int bomba1;

void iniciarBlynk(UBaseType_t core = 0, uint32_t stackDepth = 2069, UBaseType_t priority = 1);