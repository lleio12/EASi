#include "main.h"
#include "utils/DHT11.h"

// Define the lightMutex and lightLevel variables
SemaphoreHandle_t lightMutex;
float lightLevel = 0.0;

bool pump1State = false;
bool pump2State = false;
SemaphoreHandle_t pumpMutex;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Iniciando o sistema...");
  pinMode(0, INPUT);
  DHT11Util::begin(4);
  Wire.setPins(6, 7);              // Set I2C pins (same as OLED)
  Wire.begin();                    // Initialize I2C bus

  lightMutex = xSemaphoreCreateMutex();
  if (lightMutex == NULL) {
    Serial.println("Failed to create light mutex");
  }pumpMutex = xSemaphoreCreateMutex();
  if (pumpMutex == NULL) {
    Serial.println("Failed to create pump mutex");
  }

  iniciarDisplay();
  iniciarBotao();
  iniciarLightSensor();
  iniciarBlynkTask();
}

void loop() {
  // Not used due to FreeRTOS tasks
}