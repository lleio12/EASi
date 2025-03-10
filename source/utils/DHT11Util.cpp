#include "DHT11Util.h"

DHT DHT11Util::dht(0, DHT11); // Pin will be set in begin()
float DHT11Util::lastHumidity = 0;
float DHT11Util::lastTemperature = 0;
unsigned long DHT11Util::lastReadTime = 0;

void DHT11Util::begin(uint8_t pin) {
    dht.begin(pin);
}

void DHT11Util::readData() {
    unsigned long currentTime = millis();
    if (currentTime - lastReadTime >= 2000) { // Only read every 2 seconds
        lastReadTime = currentTime;
        lastHumidity = dht.readHumidity();
        lastTemperature = dht.readTemperature();
    }
}

float DHT11Util::getHumidity() {
    return lastHumidity;
}

float DHT11Util::getTemperature() {
    return lastTemperature;
}

String DHT11Util::getFormattedHumidity() {
    return String(static_cast<int>(lastHumidity));
}

String DHT11Util::getFormattedTemperature() {
    return String(static_cast<int>(lastTemperature));
}
