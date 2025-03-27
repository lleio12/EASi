#include "tasks/modeControl.h"

bool autoMode = true; // Começa no modo automático

#define MODE_AUTO_PIN 36   // Pino para ativar modo automático
#define MODE_REMOTE_PIN 35 // Pino para ativar modo remoto

TaskHandle_t autoTaskHandle = NULL;   // Handle for the auto mode task
TaskHandle_t remoteTaskHandle = NULL; // Handle for the remote mode task

void handleEventAuto(void* parameters); // Updated signature
void handleEventRemote(void* parameters); // Updated signature

void modeControlTask(void* parameters) {
    pinMode(MODE_AUTO_PIN, INPUT_PULLUP);
    pinMode(MODE_REMOTE_PIN, INPUT_PULLUP);

    for (;;) {
        if (digitalRead(MODE_AUTO_PIN) == LOW) {
            if (remoteTaskHandle != NULL) {
                vTaskDelete(remoteTaskHandle); // Kill the remote mode task
                remoteTaskHandle = NULL;      // Reset the handle
            }
            if (autoTaskHandle == NULL) {
                xTaskCreate(handleEventAuto, "Handle Event Auto", 4096, NULL, 1, &autoTaskHandle);
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        if (digitalRead(MODE_REMOTE_PIN) == LOW) {
            if (autoTaskHandle != NULL) {
                vTaskDelete(autoTaskHandle); // Kill the auto mode task
                autoTaskHandle = NULL;      // Reset the handle
            }
            if (remoteTaskHandle == NULL) {
                xTaskCreate(handleEventRemote, "Handle Event Remote", 4096, NULL, 1, &remoteTaskHandle);
            }
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void handleEventAuto(void* parameters) { // Updated signature
    autoMode = true;
    Serial.println("Modo Automático Ativado");
    vTaskDelete(NULL); // Delete the current task
}

void handleEventRemote(void* parameters) { // Updated signature
    autoMode = false;
    Serial.println("Modo Remoto Ativado");
    vTaskDelete(NULL); // Delete the current task
}

void iniciarModeControl(unsigned int, unsigned int, unsigned int) {
    TaskHandle_t modeControlHandle;
    xTaskCreatePinnedToCore(modeControlTask, "Mode Control Task", 4096, NULL, 1, &modeControlHandle, 0);
}
