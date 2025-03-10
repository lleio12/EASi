#include "display.h"
#include "display/screens.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// OLED display dimensions and I2C address
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C

// Create the display object (no reset pin, hence -1)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

static void OledTask(void *parameters) {
    Wire.setPins(6,7);
    Wire.begin();
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
        Serial.println("OLED initialization failed");
        for(;;); // Halt if initialization fails
    }

    // Initial display setup
    display.clearDisplay();
    display.setTextSize(1);             // Text size 1 (6x8 pixels per character)
    display.setRotation(2);
    display.setTextColor(SSD1306_WHITE); // White text on black background
    display.setCursor(0, 0);            // Start at top-left corner
    display.println("OLED Initialized");
    display.display();                  // Render the buffer to the screen

    // Main loop to keep the display active
    for(;;) {
        display.clearDisplay();
        draw();
        display.display();
        
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second
    }
}

// Function to start the OLED task
void iniciarDisplay(UBaseType_t core, uint32_t stackDepth, UBaseType_t priority) {
    TaskHandle_t oledTask;
    xTaskCreatePinnedToCore(
        OledTask,            // Task function
        "OLED Display Task", // Task name
        stackDepth,          // Stack depth in words
        NULL,                // Task parameters (none needed)
        priority,            // Task priority
        &oledTask,           // Task handle (optional)
        core                 // Core to run the task on
    );
}