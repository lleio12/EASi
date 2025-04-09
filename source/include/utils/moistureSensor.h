#pragma once
#include <Arduino.h> 

namespace MoistureSensorUtil {
    // Constants for sensor identification
    enum SensorId {
        SENSOR_1 = 0,
        SENSOR_2 = 1,
        SENSOR_3 = 2,
        MAX_SENSORS = 3
    };

    void begin(uint8_t pin, SensorId id = SENSOR_1);
    
    int getRawValue(SensorId id = SENSOR_1);
    
    float getMoisturePercentage(SensorId id = SENSOR_1);
}
