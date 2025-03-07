#include "sensorHumidade.h"

void iniciarMoistureSensor(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority)
{
    buzzerQueue = xQueueCreate(10, sizeof(BuzzerCommand));
    xTaskCreatePinnedToCore(
        buzzerTask,
        "Buzzer Task",
        stackDepth,
        NULL,
        priority,
        NULL,
        core);
}