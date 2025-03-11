#include "DHT11.h"

namespace DHT11Util {
    // Static pointer to DHT object, initialized in begin()
    static DHT* dht = nullptr;

    // Static mutex handle for thread safety
    static SemaphoreHandle_t mutex = nullptr;

    void begin(uint8_t pin) {
        // Clean up if already initialized
        if (dht != nullptr) {
            delete dht;
        }
        // Create new DHT object with pin and DHT11 type
        dht = new DHT(pin, DHT11);
        dht->begin();

        // Create mutex if not already created
        if (mutex == nullptr) {
            mutex = xSemaphoreCreateMutex();
            if (mutex == NULL) {
                Serial.println("Failed to create mutex");
                // Error handling could be expanded (e.g., abort)
            }
        }
    }

    float airTemperature() {
        if (dht == nullptr) {
            return NAN;  // Sensor not initialized
        }
        // Acquire mutex with infinite wait
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            float temp = dht->readTemperature();
            xSemaphoreGive(mutex);
            return temp;
        } else {
            return NAN;  // Mutex acquisition failed
        }
    }

    float airHumidity() {
        if (dht == nullptr) {
            return NAN;  // Sensor not initialized
        }
        // Acquire mutex with infinite wait
        if (xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE) {
            float hum = dht->readHumidity();
            xSemaphoreGive(mutex);
            return hum;
        } else {
            return NAN;  // Mutex acquisition failed
        }
    }

    String getFormattedTemperature() {
        float temp = airTemperature();
        if (isnan(temp)) {
            return "N/A";  // Indicate invalid reading
        } else {
            return String(temp, 1) + " C";  // e.g., "23.5 C"
        }
    }

    String getFormattedHumidity() {
        float hum = airHumidity();
        if (isnan(hum)) {
            return "N/A";  // Indicate invalid reading
        } else {
            return String(hum, 1) + " %";  // e.g., "45.2 %"
        }
    }
}