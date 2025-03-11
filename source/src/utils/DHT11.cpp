#include "utils/DHT11.h"

namespace DHT11Util {
    static DHT* dht = nullptr;
    static SemaphoreHandle_t mutex = nullptr;

    void begin(uint8_t pin) {
        if (dht != nullptr) {
            delete dht;
        }
        dht = new DHT(pin, DHT11);
        dht->begin();
        if (mutex == nullptr) {
            mutex = xSemaphoreCreateMutex();
            if (mutex == NULL) {
                Serial.println("Failed to create mutex");
            }
        }
    }

    float airTemperature() {
        if (dht == nullptr) return NAN;
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            float temp = dht->readTemperature();
            xSemaphoreGive(mutex);
            return temp;
        }
        return NAN;
    }

    float airHumidity() {
        if (dht == nullptr) return NAN;
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            float hum = dht->readHumidity();
            xSemaphoreGive(mutex);
            return hum;
        }
        return NAN;
    }

    String getFormattedTemperature() {
        float temp = airTemperature();
        if (isnan(temp)) {
            return "N/A";  // Handle invalid readings
        } else {
            return String(static_cast<int>(temp));  // Convert to integer and then to string
        }
    }

    String getFormattedHumidity() {
        float hum = airHumidity();
        if (isnan(hum)) {
            return "N/A";  // Handle invalid readings
        } else {
            return String(static_cast<int>(hum));  // Convert to integer and then to string
        }
    }
}