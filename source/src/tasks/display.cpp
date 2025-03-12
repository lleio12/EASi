#include "tasks/display.h"
#include "display/screens.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "main.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int currentScreen = 0;  // 0 para splash, 1 para DHT11

static void OledTask(void *parameters) {
    Wire.setPins(6, 7);
    Wire.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED initialization failed");
        for(;;);
    } else {
        Serial.println("Display OLED iniciou com sucesso");
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setRotation(2);

    splashScreen();  // Exibe a tela inicial
    display.display();
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    for(;;) {
        display.clearDisplay();
        if (currentScreen == 0) {
            DHT11Screen();  // Exibe a tela do DHT11
        } else {
            cuideDasPlantas();  // Exibe a segunda tela
        }
        display.display();
        vTaskDelay(100 / portTICK_PERIOD_MS);  // Atualiza a tela a cada 100ms
    }
}

static void buttonTask(void *parameters) {
    int lastButtonState = HIGH;  // Último estado do botão (HIGH por padrão)

    for(;;) {
        int buttonState = digitalRead(0);  // Lê o estado atual do pino 2
        if (buttonState == LOW && lastButtonState == HIGH) {
            // Botão foi pressionado (transição de HIGH para LOW)
            currentScreen = (currentScreen + 1) % 2;  // Alterna entre 0 e 1
            Serial.println("Botão pressionado");
            vTaskDelay(50 / portTICK_PERIOD_MS);  // Debounce simples de 50ms
        }
        lastButtonState = buttonState;  // Atualiza o último estado
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Pequeno delay para não sobrecarregar a CPU
    }
}

void iniciarDisplay(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority) {
    TaskHandle_t oledTask;
    xTaskCreatePinnedToCore(OledTask, "OLED Display Task", stackDepth, NULL, priority, &oledTask, core);
}

void iniciarBotao(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority) {
    TaskHandle_t buttonTaskHandle;
    xTaskCreatePinnedToCore(buttonTask, "Button Task", stackDepth, NULL, priority, &buttonTaskHandle, core);
}