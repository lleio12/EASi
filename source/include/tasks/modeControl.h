#pragma once
#include <Arduino.h>

extern bool autoMode; // Variável global para indicar modo automático
extern bool remoteMode; // Variável global para indicar modo remoto

void iniciarModeControl(UBaseType_t core = 0, uint32_t stackDepth = 4096, UBaseType_t priority = 1);