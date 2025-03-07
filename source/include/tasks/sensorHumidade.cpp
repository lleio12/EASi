#include "sensorHumidade.h"

void moistureSensor(void *parameters){
    
    for(;;) {}
}

void iniciarMoistureSensor(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority)
{
    TaskHandle_t moistureSensor0;
    xTaskCreatePinnedToCore(
        moistureSensor,
        "Clock",
        stackDepth,
        NULL,
        priority,
        &moistureSensor0,
        core);
}