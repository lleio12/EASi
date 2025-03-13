#include "tasks/lightSensor.h"
#include <BH1750.h>

extern float lightLevel;
extern SemaphoreHandle_t lightMutex;

void lightSensorTask(void *parameters) {
    BH1750 lightMeter;  // Default I2C address 0x23
    lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE); // High resolution, continuous mode
    
    for (;;) {
        if (xSemaphoreTake(lightMutex, portMAX_DELAY) == pdTRUE) {
            lightLevel = lightMeter.readLightLevel(); // Read light level in lux
            xSemaphoreGive(lightMutex);
        }
        vTaskDelay(500 / portTICK_PERIOD_MS); // Update every 500ms
    }
}

void iniciarLightSensor(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority) {
    TaskHandle_t lightSensorHandle;
    xTaskCreatePinnedToCore(lightSensorTask, "Light Sensor Task", stackDepth, NULL, priority, &lightSensorHandle, core);
}