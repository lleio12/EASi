#include "main.h"
#include "utils/DHT11Util.h"

// bh --> 0x23
// oled --> 0x3D / 0x3C

void setup () {
  Serial.begin(115200);

  delay(500);

  Serial.println("Iniciando o sistema...");

  // Initialize DHT11 on pin 4
  DHT11Util::begin(4);

  iniciarDisplay();
}

void loop(){
  // nao utilizado devido a tasks do FreeRTOS
}