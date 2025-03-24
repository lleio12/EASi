#include "tasks/blynk.h"
#include "blynkConfig.h"
#include "utils/DHT11.h"
#include "main.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "iphone de Luciana";
char pass[] = "fthdp6zzbr";

int pinoBomba1 = 17, pinoBomba2 = 16, pinoBomba3 = 18, pinoUV = 20;

BLYNK_WRITE(V1) { // bomba 1
  int value = param.asInt(); // Recebe o valor do aplicativo Blynk
  digitalWrite(pinoBomba1, value);  // Define o estado do pino 16
}

BLYNK_WRITE(V2) { // bomba 2
  int value = param.asInt();
  digitalWrite(pinoBomba2, value);
}

BLYNK_WRITE(V3) { // bomba 3
  int value = param.asInt();
  digitalWrite(pinoBomba3, value);
}

BLYNK_WRITE(V0) { // luzes uv
  int value = param.asInt();
  digitalWrite(pinoUV, value);
}

void blynkTask(void* parameters) {
  // Configurar os pinos 16, 17 e 18 como saídas
  pinMode(pinoBomba2, OUTPUT);
  digitalWrite(pinoBomba2, HIGH); // Estado inicial baixo
  pinMode(pinoBomba1, OUTPUT);
  digitalWrite(pinoBomba1, HIGH);
  pinMode(pinoBomba3, OUTPUT);
  digitalWrite(pinoBomba3, HIGH);
  pinMode(pinoUV, OUTPUT);
  digitalWrite(pinoUV, HIGH);

  Blynk.begin(auth, ssid, pass); // Inicia a conexão com o Blynk

  unsigned long lastMoistureSendTime = 0; // Track the last time moisture data was sent
  unsigned long lastDHT11SendTime = 0; // Track the last time DHT11 data was sent
  unsigned long lastLuxSendTime = 0; // Track the last time lux data was sent

  for(;;) {
    Blynk.run();

    // Send soil moisture data to V4 every 5 seconds
    unsigned long currentMillis = millis();
    if (currentMillis - lastMoistureSendTime >= 5000) {
      float moisture = MoistureSensorUtil::getMoisturePercentage(); // Replace with your sensor reading
      if (moisture >= 0) {
        Blynk.virtualWrite(V4, moisture); // Send value to V4 (gauge)
      }

      float temperature = DHT11Util::getFormattedTemperature().toFloat();
      float humidity = DHT11Util::getFormattedHumidity().toFloat();

      Blynk.virtualWrite(V7, temperature); // Send temperature to V7 (gauge)
      Blynk.virtualWrite(V8, humidity); // Send humidity to V8 (gauge)

      float currentLight;
      if (xSemaphoreTake(lightMutex, portMAX_DELAY) == pdTRUE) {
        currentLight = lightLevel; // Lê o valor do sensor de luz
        xSemaphoreGive(lightMutex);
        Blynk.virtualWrite(V5, currentLight); // Envia para o datastream V5
      }

      lastMoistureSendTime = currentMillis; // Update the last send time
    }

    vTaskDelay(100 / portTICK_PERIOD_MS); // Atraso de 100ms
  }
}

void iniciarBlynk(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority)
{
    TaskHandle_t blynk;
    xTaskCreatePinnedToCore(
        blynkTask,
        "A tarefa do Blynk",
        stackDepth,
        NULL,
        priority,
        &blynk,
        core);
}