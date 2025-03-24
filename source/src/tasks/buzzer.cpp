#include "tasks/buzzer.h"
#include "main.h"

#define BUZZER_PIN 21
#define PWM_CHANNEL 0 // Canal PWM (0-15 no ESP32)
#define PWM_FREQ 2000 // Frequência fixa (ex.: 2kHz, comum para buzzers)
#define PWM_RESOLUTION 8 // Resolução de 8 bits (0-255)

void buzzerTask(void* parameters) {
    // Configura o canal PWM
    ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcAttachPin(BUZZER_PIN, PWM_CHANNEL);
    ledcWrite(PWM_CHANNEL, 0); // Começa desligado (duty cycle 0)

    for(;;) {
        float currentLight;
        if (xSemaphoreTake(lightMutex, portMAX_DELAY) == pdTRUE) {
            currentLight = lightLevel;
            xSemaphoreGive(lightMutex);
        } else {
            currentLight = -1.0;
        }

        if (currentLight == 0.0) {
            // Liga o buzzer com 50% de duty cycle (metade da potência máxima)
            ledcWrite(PWM_CHANNEL, 255); // 128 de 255 = 50%
            vTaskDelay(200 / portTICK_PERIOD_MS);
            ledcWrite(PWM_CHANNEL, 0); // Desliga
            vTaskDelay(200 / portTICK_PERIOD_MS);
        } else {
            ledcWrite(PWM_CHANNEL, 0); // Desligado
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
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