#include "tasks/blynkHandler.h"
#include "blynkConfig.h"
#include <WiFi.h>
#include <WiFiClient.h>
// Include minimal Blynk header if needed for Blynk.run(), etc.
#include <Blynk/BlynkApi.h> // May be required; test compilation
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char ssid[] = "Nigga Shark";
char pass[] = "nigger69";

// Relay pin
#define RELAY_PIN 3

// Virtual pins for Blynk
#define V_RELAY 1

static void blynkTask(void *parameters) {
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    while (1) {
        Blynk.run();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

BLYNK_WRITE(V_RELAY) {
    int pinValue = param.asInt();
    digitalWrite(RELAY_PIN, pinValue);
}

void iniciarBlynkTask(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority) {
    TaskHandle_t blynkTaskHandle;
    xTaskCreatePinnedToCore(blynkTask, "Blynk Task", stackDepth, NULL, priority, &blynkTaskHandle, core);
}