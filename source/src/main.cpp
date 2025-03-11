#include "main.h"
#include "utils/DHT11.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Iniciando o sistema...");
  DHT11Util::begin(4);
  iniciarDisplay();
}

void loop() {
  // Not used due to FreeRTOS tasks
}