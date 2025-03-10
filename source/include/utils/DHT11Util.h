#pragma once
#include <DHT.h>
#include "DHT11Util.cpp"

class DHT11Util {
public:
    static void begin(uint8_t pin);
    static float getHumidity();
    static float getTemperature();
    static String getFormattedHumidity();
    static String getFormattedTemperature();

private:
    static DHT dht;
    static float lastHumidity;
    static float lastTemperature;
    static unsigned long lastReadTime;
    
    static void readData();
};