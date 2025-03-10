#ifndef DHT11UTIL_H
#define DHT11UTIL_H

#include <DHT.h>

class DHT11Util {
public:
    static void begin(uint8_t pin);
    static void readData();
    static float getHumidity();
    static float getTemperature();
    static String getFormattedHumidity();
    static String getFormattedTemperature();

private:
    static DHT dht;
    static float lastHumidity;
    static float lastTemperature;
    static unsigned long lastReadTime;
};

#endif // DHT11UTIL_H
