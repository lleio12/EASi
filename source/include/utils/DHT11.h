#pragma once
#include <Arduino.h>  // For basic Arduino functions and FreeRTOS support
#include <DHT.h>      // Adafruit DHT library for sensor interaction

namespace DHT11Util {
    // Initialize the DHT11 sensor with the specified pin
    void begin(uint8_t pin);

    // Get temperature in Celsius (returns float)
    float airTemperature();

    // Get humidity in percentage (returns float)
    float airHumidity();

    // Get formatted temperature string (e.g., "23.5 C")
    String getFormattedTemperature();

    // Get formatted humidity string (e.g., "45.2 %")
    String getFormattedHumidity();
}