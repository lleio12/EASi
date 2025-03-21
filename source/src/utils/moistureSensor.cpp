#include "utils/moistureSensor.h"

namespace MoistureSensorUtil {
    static uint8_t sensorPin = 0;

    void begin(uint8_t pin) {
        sensorPin = pin;
        pinMode(sensorPin, INPUT);
    }

    int getRawValue() {
        if (sensorPin == 0) return -1;
        return analogRead(sensorPin);  
    }

    float getMoisturePercentage() {
        int rawValue = getRawValue();
        if (rawValue == -1) return -1.0;

        const int maxValue = 3000;
        const int minValue = 1018;    

        rawValue = constrain(rawValue, minValue, maxValue);

        float percentage = 100.0 * (1.0 - static_cast<float>(rawValue - minValue) / (maxValue - minValue));
        return percentage;
    }
}