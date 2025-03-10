// DHT11

#include "sensorDHT11.h"

// Definições do sensor DHT11
#define DHTPIN 4        // Pino onde o DHT11 está conectado (ajuste conforme necessário)
#define DHTTYPE DHT11   // Tipo do sensor (DHT11)

// Criando uma instância do sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

void HumTemp(void *parameters) {
    dht.begin();
    Serial.println("DHT11 Iniciado");

    for(;;) {
        float humidade = dht.readHumidity();
        float temperatura = dht.readTemperature();

        if (isnan(humidade) || isnan(temperatura)) {
            Serial.println("Falha ao ler do sensor DHT11!");
        } else {
            Serial.print("Humidade: ");
            Serial.print(humidade);
            Serial.print(" %\t");
            Serial.print("Temperatura: ");
            Serial.print(temperatura);
            Serial.println(" *C");
        }

        vTaskDelay(1450 / portTICK_PERIOD_MS);
    }
}

void iniciarHumTemp(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority)
{
    TaskHandle_t humTemp0;
    xTaskCreatePinnedToCore(
        HumTemp,
        "Humidity and Temperature Sensor (DHT11)",
        stackDepth,
        NULL,
        priority,
        &humTemp0,
        core);
}