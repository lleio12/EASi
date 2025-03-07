#include "sensorHumidade.h"

void HumTemp(void *parameters){
    
    for(;;) {}
}

void iniciarHumTemp(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority)
{
    TaskHandle_t humTemp0;
    xTaskCreatePinnedToCore(
        HumTemp,
        "Humidity Temperature Sensor",
        stackDepth,
        NULL,
        priority,
        &humTemp0,
        core);
}