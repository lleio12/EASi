#include "utils/moistureSensor.h"

namespace MoistureSensorUtil {
    static uint8_t sensorPins[MAX_SENSORS] = {0, 0, 0};

    void begin(uint8_t pin, SensorId id) {
        if (id >= MAX_SENSORS) return;
        sensorPins[id] = pin;
        pinMode(sensorPins[id], INPUT);
    }

    int getRawValue(SensorId id) {
        if (id >= MAX_SENSORS || sensorPins[id] == 0) return -1;
        return analogRead(sensorPins[id]);  
    }

    float getMoisturePercentage(SensorId id) {
        int rawValue = getRawValue(id);
        if (rawValue == -1) return -1.0;

        const int maxValue = 3000;
        const int minValue = 100;    

        rawValue = constrain(rawValue, minValue, maxValue);

        float percentage = 100.0 * (1.0 - static_cast<float>(rawValue - minValue) / (maxValue - minValue));
        return percentage;
    }
}