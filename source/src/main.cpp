#include "main.h"
#include "utils/DHT11.h"

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Iniciando o sistema...");
  pinMode(0, INPUT);
  DHT11Util::begin(4);
  iniciarDisplay();
  iniciarBotao();
}

void loop() {
  // Not used due to FreeRTOS tasks
}