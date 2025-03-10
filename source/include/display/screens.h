#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "tasks/sensorDHT11.h"

// Declare the display object
extern Adafruit_SSD1306 display;

void draw(void) {
    display.clearDisplay();

    display.setTextColor(1);
    display.setTextSize(1);
    display.setTextWrap(false);
    display.setCursor(15, 16);
    display.print("HUM ar");

    display.setTextSize(2);
    display.setCursor(22, 0);
    int truncatedHumidity = static_cast<int>(humidade);
    display.print(truncatedHumidity);

    display.setTextSize(1);
    display.setCursor(71, 16);
    display.print("TEMP ar");

    display.setTextSize(2);
    display.setCursor(81, 0);
    int truncatedTemperature = static_cast<int>(temperatura);
    display.print(truncatedTemperature);

    display.display();
}