#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "../utils/DHT11Util.h"

// Declare the display object
extern Adafruit_SSD1306 display;

void draw(void) {
    display.clearDisplay();
    
    display.setTextColor(1);
    display.setTextSize(1);
    display.setCursor(15, 16);
    display.print("HUM ar");

    display.setTextSize(2);
    display.setCursor(22, 0);
    display.print(DHT11Util::getFormattedHumidity());

    display.setTextSize(1);
    display.setCursor(71, 16);
    display.print("TEMP ar");

    display.setTextSize(2);
    display.setCursor(81, 0);
    display.print(DHT11Util::getFormattedTemperature());

    display.display();
}