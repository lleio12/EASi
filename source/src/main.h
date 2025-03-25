#include <Arduino.h>
#include <Wire.h>
#include "tasks.h"
#include "utils/DHT11.h"
#include "utils/moistureSensor.h"
#include "utils/bombas.h"

extern float lightLevel;
extern SemaphoreHandle_t lightMutex;