#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "utils/DHT11.h"

extern Adafruit_SSD1306 display;

static const unsigned char PROGMEM image_Layer_6_bits[] = {0xe0, 0xe0, 0xe0};

void draw(void) {
    display.clearDisplay();

    display.setTextColor(1);
    display.setTextSize(1);
    display.setTextWrap(false);
    display.setCursor(15, 16);
    display.print("HUM ar");

    display.setTextSize(2);
    display.setCursor(15, 0);
    display.print(DHT11Util::getFormattedHumidity() + "%"); // Use formatted integer value
    display.setTextSize(1);
    display.setCursor(71, 16);
    display.print("TEMP ar");

    display.setTextSize(2);
    display.setCursor(72, 0);
    display.print(DHT11Util::getFormattedTemperature()); // Use formatted integer value

    display.setCursor(100, 0);
    display.print("C");

    display.drawBitmap(96, 1, image_Layer_6_bits, 3, 3, 1);

    display.display();
}