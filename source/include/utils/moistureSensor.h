#pragma once
#include <Arduino.h> 

namespace MoistureSensorUtil {
    void begin(uint8_t pin);

    int getRawValue();

    float getMoisturePercentage();
}
