#include "DHT11Util.h"
#include <Arduino.h>

DHT DHT11Util::dht(0, DHT11); // Pin will be set in begin()
float DHT11Util::lastHumidity = 0;
float DHT11Util::lastTemperature = 0;
unsigned long DHT11Util::lastReadTime = 0;

void DHT11Util::begin(uint8_t pin) {
    dht.setup(pin);
    dht.begin();
}

void DHT11Util::readData() {
    if(millis() - lastReadTime > 2000) { // Read every 2 seconds
        lastHumidity = dht.getHumidity();
        lastTemperature = dht.getTemperature();
        lastReadTime = millis();
    }
}

float DHT11Util::getHumidity() {
    readData();
    return lastHumidity;
}

float DHT11Util::getTemperature() {
    readData();
    return lastTemperature;
}

String DHT11Util::getFormattedHumidity() {
    int value = static_cast<int>(getHumidity());
    return (value < 10) ? "0" + String(value) : String(value);
}

String DHT11Util::getFormattedTemperature() {
    int value = static_cast<int>(getTemperature());
    return (value < 10) ? "0" + String(value) : String(value);
}