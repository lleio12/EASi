#include <Arduino.h>
#include <Wire.h>
#include "tasks.h"

extern float lightLevel;
extern SemaphoreHandle_t lightMutex;