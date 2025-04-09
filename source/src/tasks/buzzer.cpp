#include "tasks/buzzer.h"
#include "main.h"

#define BUZZER_PIN 21 // Pino conectado ao buzzer ativo

void buzzerTask(void* parameters) {
    pinMode(BUZZER_PIN, OUTPUT); // Configura o pino como saída
    digitalWrite(BUZZER_PIN, HIGH); // Começa desligado
    vTaskDelay(150 / portTICK_PERIOD_MS); // Aguarda 1 segundo
    digitalWrite(BUZZER_PIN, LOW); // Começa desligado
    vTaskDelay(150 / portTICK_PERIOD_MS); // Aguarda 1 segundo
    digitalWrite(BUZZER_PIN, HIGH); // Começa desligado
    vTaskDelay(150 / portTICK_PERIOD_MS); // Aguarda 1 segundo
    digitalWrite(BUZZER_PIN, LOW); // Começa desligado

    for (;;) {
        // Lógica para ativar o buzzer
        float currentLight;
        if (xSemaphoreTake(lightMutex, portMAX_DELAY) == pdTRUE) {
          currentLight = lightLevel; // Lê o valor do sensor de luz
          xSemaphoreGive(lightMutex);
          if (currentLight < 100) { // Se a luz estiver abaixo de 100
            digitalWrite(BUZZER_PIN, HIGH); // Liga o buzzer
            vTaskDelay(1000 / portTICK_PERIOD_MS); // Aguarda 1 segundo
            digitalWrite(BUZZER_PIN, LOW); // Desliga o buzzer
            vTaskDelay(1000 / portTICK_PERIOD_MS); // Aguarda 1 segundo
          } else {
            digitalWrite(BUZZER_PIN, LOW); // Desliga o buzzer
          }
        }
        vTaskDelay(12 / portTICK_PERIOD_MS); // Atraso de 100ms
    }
}

void iniciarBuzzer(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority) {
    TaskHandle_t buzzerHandle;
    xTaskCreatePinnedToCore(
        buzzerTask,
        "Buzzer Task",
        stackDepth,
        NULL,
        priority,
        &buzzerHandle,
        core);
}