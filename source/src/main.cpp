#include "main.h"

// bh --> 0x23
// oled --> 0x3D / 0x3C

void setup () {
  Serial.begin(115200);

  delay(500);

  Serial.println("Iniciando o sistema...");

  iniciarHumTemp();
  iniciarDisplay();
}

void loop(){
  // nao utilizado devido a tasks do FreeRTOS
}