#include "main.h"

// Define the lightMutex and lightLevel variables
SemaphoreHandle_t lightMutex;
float lightLevel = 0.0;

void setup() {
    Serial.begin(115200);
    delay(500);    Serial.println("Iniciando o sistema...");
    pinMode(0, INPUT);
    DHT11Util::begin(4);
    
    // Initialize all moisture sensors
    MoistureSensorUtil::begin(15, MoistureSensorUtil::SENSOR_1);
    MoistureSensorUtil::begin(8, MoistureSensorUtil::SENSOR_2);
    MoistureSensorUtil::begin(3, MoistureSensorUtil::SENSOR_3);
    
    BombasUtil::begin();

    Wire.setPins(6, 7); // Set I2C pins (same as OLED)
    Wire.begin();       // Initialize I2C bus

    lightMutex = xSemaphoreCreateMutex();
    if (lightMutex == NULL) {
        Serial.println("Failed to create light mutex");
    }

    iniciarDisplay();
    iniciarBotao();
    iniciarLightSensor();
    iniciarBlynk();
    iniciarBuzzer();
}

void loop() {
    // Not used due to FreeRTOS tasks
}