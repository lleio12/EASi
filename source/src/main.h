#include <Arduino.h>
#include <Wire.h>
#include "tasks.h"

extern float lightLevel;
extern SemaphoreHandle_t lightMutex;

extern bool pump1State;         // Pump 1 state
extern bool pump2State;         // Pump 2 state
extern bool pump3State;         // Pump 2 state
extern SemaphoreHandle_t pumpMutex; // Mutex for pump states