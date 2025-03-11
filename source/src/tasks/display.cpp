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
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setRotation(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("OLED Initialized");
    display.display();

    for(;;) {
        display.clearDisplay();
        draw();
        display.display();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void iniciarDisplay(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority) {
    TaskHandle_t oledTask;
    xTaskCreatePinnedToCore(OledTask, "OLED Display Task", stackDepth, NULL, priority, &oledTask, core);
}