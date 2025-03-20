#include "tasks/sensorHumidade.h"
#define MOISTURE_SENSOR_PIN 15  
#define LED_PIN 4               
#define THRESHOLD 2000          

void moistureSensor(void *parameters){

    pinMode(LED_PIN, OUTPUT);    // Configura o pino do LED como saída
    digitalWrite(LED_PIN, LOW);  // LED começa desligado
    Serial.begin(115200);        // Inicia a comunicação serial para debug
   
   
    for(;;) {
        int moistureValue = analogRead(MOISTURE_SENSOR_PIN);  // Lê o valor do sensor
        Serial.println(moistureValue);                       // Mostra o valor no monitor serial
        
        if (moistureValue > THRESHOLD) { // Solo seco
          digitalWrite(LED_PIN, HIGH);   // Liga o LED
        } else {                         // Solo úmido
          digitalWrite(LED_PIN, LOW);    // Desliga o LED
        }
      
        delay(1000); // Aguarda 1 segundo antes de ler novamente
    }
}

void iniciarMoistureSensor(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority)
{
    TaskHandle_t moistureSensor0;
    xTaskCreatePinnedToCore(
        moistureSensor,
        "Moisture Sensor",
        stackDepth,
        NULL,
        priority,
        &moistureSensor0,
        core);
}