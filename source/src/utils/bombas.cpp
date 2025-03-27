#include "utils/bombas.h"

namespace BombasUtil {
    static const int pumpPins[3] = {17, 16, 18}; // Pinos: bomba1, bomba2, bomba3

    void begin() {
        for (int i = 0; i < 3; i++) {
            pinMode(pumpPins[i], OUTPUT);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            digitalWrite(pumpPins[i], LOW); // Inicializa desligado (LOW = off)
        }
    }

    void bomba(int index, int state) {
        if (index >= 0 && index < 3) {
            digitalWrite(pumpPins[index], state ? HIGH : LOW); // 1 = HIGH (on), 0 = LOW (off)
        }
    }
}