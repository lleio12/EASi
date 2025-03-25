#pragma once
#include <Arduino.h>

namespace BombasUtil {
    void begin();                     // Inicializa os pinos das bombas
    void bomba(int index, int state); // Controla uma bomba específica (index: 0-2, state: 0 ou 1)
}