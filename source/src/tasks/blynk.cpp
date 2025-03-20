#include "tasks/blynk.h"
#include "blynkConfig.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Nigga Shark";
char pass[] = "nigger69";

// Funções BLYNK_WRITE para controlar os pinos
BLYNK_WRITE(V1) {
  int value = param.asInt(); // Recebe o valor do aplicativo Blynk
  digitalWrite(17, value);  // Define o estado do pino 16
}

BLYNK_WRITE(V2) {
  int value = param.asInt(); // Recebe o valor do aplicativo Blynk
  digitalWrite(16, value);  // Define o estado do pino 17
}

BLYNK_WRITE(V3) {
  int value = param.asInt(); // Recebe o valor do aplicativo Blynk
  digitalWrite(18, value);  // Define o estado do pino 18
}

void blynkTask(void* parameters) {
  // Configura os pinos 16, 17 e 18 como saídas
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH); // Estado inicial baixo
  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH); // Estado inicial baixo
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH); // Estado inicial baixo

  Blynk.begin(auth, ssid, pass); // Inicia a conexão com o Blynk

  for(;;) {
    Blynk.run(); // Executa o manipulador do Blynk

    // Send soil moisture data to V4 every second
    float moisture = MoistureSensorUtil::getMoisturePercentage(); // Replace with your sensor reading
    if (moisture >= 0) {
      Blynk.virtualWrite(V4, moisture); // Send value to V4 (gauge)
    }

    vTaskDelay(50 / portTICK_PERIOD_MS); // Atraso de 100ms
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