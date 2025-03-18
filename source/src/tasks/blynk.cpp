#include "tasks/blynk.h"
#include "blynkConfig.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Nigga Shark";
char pass[] = "nigger69";

void blynkTask(void* parameters) {
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  Blynk.virtualWrite(V5, 15);
  Blynk.begin(auth, ssid, pass);

  for(;;) {
    Blynk.run();
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