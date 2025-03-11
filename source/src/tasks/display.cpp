#include "tasks/display.h"
#include "display/screens.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

static void OledTask(void *parameters) {
    Wire.setPins(6,7);
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

    splashScreen();
    display.display();
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    for(;;) {
        display.clearDisplay();
        DHT11Screen();
        display.display();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void iniciarDisplay(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority) {
    TaskHandle_t oledTask;
    xTaskCreatePinnedToCore(OledTask, "OLED Display Task", stackDepth, NULL, priority, &oledTask, core);
}