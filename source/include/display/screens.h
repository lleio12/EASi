#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "utils/DHT11.h"
#include "main.h"

extern Adafruit_SSD1306 display;

// Declare the lightMutex and lightLevel variables as extern
extern SemaphoreHandle_t lightMutex;
extern float lightLevel;

static const unsigned char PROGMEM image_Layer_6_bits[] = {0xe0, 0xe0, 0xe0};

static const unsigned char PROGMEM image_Layer_4_bits[] = {0x83, 0x85, 0x02};
// rain particle
static const unsigned char PROGMEM image_Layer_9__copy__bits[] = {0x30, 0x30, 0xc0, 0xc0};

static const unsigned char PROGMEM image_Layer_9_1_bits[] = {0x03, 0xc3, 0xfc, 0x00, 0x03, 0xc3, 0xfc, 0x00, 0x3c, 0x3c, 0x03, 0xf0, 0x3c, 0x3c, 0x03, 0xf0, 0xc0, 0xc0, 0x00, 0xcc, 0xc0, 0xc0, 0x00, 0xcc, 0xc0, 0x00, 0xc0, 0x0c, 0xc0, 0x00, 0xc0, 0x0c, 0x3c, 0xc0, 0x30, 0x3c, 0x3c, 0xc0, 0x30, 0x3c, 0x0f, 0x3f, 0xcf, 0xc0, 0x0f, 0x3f, 0xcf, 0xc0};
// letter S
static const unsigned char PROGMEM image_Layer_10_bits[] = {0x3f, 0xc0, 0x3f, 0xc0, 0xff, 0xf0, 0xff, 0xf0, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xff, 0xc0, 0xff, 0xc0, 0x3f, 0xf0, 0x3f, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0x3f, 0xc0, 0x3f, 0xc0};
// letter A
static const unsigned char PROGMEM image_Layer_10_1_bits[] = {0x3c, 0x00, 0x3c, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xc0, 0xff, 0xc0, 0xf3, 0xf0, 0xf3, 0xf0, 0xf0, 0xfc, 0xf0, 0xfc, 0xf0, 0x3c, 0xf0, 0x3c, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xf0, 0x3c, 0xf0, 0x3c, 0xf0, 0x3c, 0xf0, 0x3c};
// letter E
static const unsigned char PROGMEM image_Layer_10_2_bits[] = {0x3f, 0xf0, 0x3f, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xff, 0xf0, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0xff, 0xf0, 0xff, 0xf0, 0x3f, 0xf0, 0x3f, 0xf0};
// letter I
static const unsigned char PROGMEM image_Layer_11_bits[] = {0x3f, 0xc0, 0x3f, 0xc0, 0xff, 0xf0, 0xff, 0xf0, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0xff, 0xf0, 0xff, 0xf0, 0x3f, 0xc0, 0x3f, 0xc0};
// tree
static const unsigned char PROGMEM image_Layer_17_bits[] = {0x00, 0x3f, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x03, 0xc0, 0xc0, 0x00, 0x03, 0xc0, 0xc0, 0x00, 0x03, 0x0c, 0xfc, 0x00, 0x03, 0x0c, 0xfc, 0x00, 0x0f, 0xcf, 0xc3, 0x00, 0x0f, 0xcf, 0xc3, 0x00, 0x3c, 0x3c, 0x0f, 0x00, 0x3c, 0x3c, 0x0f, 0x00, 0xc0, 0xc0, 0xf0, 0xc0, 0xc0, 0xc0, 0xf0, 0xc0, 0xc0, 0x3c, 0x00, 0xc0, 0xc0, 0x3c, 0x00, 0xc0, 0x3c, 0xc0, 0xf3, 0x00, 0x3c, 0xc0, 0xf3, 0x00, 0x0f, 0x33, 0x0f, 0x00, 0x0f, 0x33, 0x0f, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00, 0xcc, 0xc0, 0x00, 0x00, 0xcc, 0xc0, 0x00, 0x03, 0x33, 0x30, 0x00, 0x03, 0x33, 0x30, 0x00};
// sad face ):
static const unsigned char PROGMEM image_FaceNopower_bits[] = {0x00,0x00,0x00,0x00,0x03,0x00,0x06,0x00,0x03,0x00,0x06,0x00,0x07,0x00,0x07,0x00,0x7e,0x00,0x03,0xf0,0x7c,0x00,0x01,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xc0,0x00,0x00,0x30,0x60,0x00,0x00,0x7f,0xf0,0x00,0x00,0x7f,0xf0,0x00,0x00,0x70,0x70,0x00,0x00,0x00,0x00,0x00};

void DHT11Screen(void)
{
   display.clearDisplay();
   display.setTextColor(1);
   display.setTextSize(1);
   display.setTextWrap(false);
   display.setCursor(15, 16);
   display.print("HUM ar");
   display.setTextSize(2);
   display.setCursor(15, 0);
   display.print(DHT11Util::getFormattedHumidity() + "%");  // Use formatted integer value
   display.setTextSize(1);
   display.setCursor(71, 16);
   display.print("TEMP ar");
   display.setTextSize(2);
   display.setCursor(72, 0);
   display.print(DHT11Util::getFormattedTemperature());  // Use formatted integer value
   display.setCursor(100, 0);
   display.print("C");
   display.drawBitmap(96, 1, image_Layer_6_bits, 3, 3, 1);
}


void splashScreen(void)
 {
     display.clearDisplay();
 
     display.drawBitmap(69, 12, image_Layer_4_bits, 8, 3, 0);
 
     display.drawBitmap(18, 16, image_Layer_9__copy__bits, 4, 4, 1);
 
     display.drawBitmap(14, 16, image_Layer_9__copy__bits, 4, 4, 1);
 
     display.drawBitmap(0, 2, image_Layer_9_1_bits, 30, 12, 1);
 
     display.drawBitmap(25, 14, image_Layer_9__copy__bits, 4, 4, 1);
 
     display.drawBitmap(68, 2, image_Layer_10_bits, 12, 20, 1);
 
     display.drawBitmap(52, 2, image_Layer_10_1_bits, 14, 20, 1);
 
     display.drawBitmap(38, 2, image_Layer_10_2_bits, 12, 20, 1);
 
     display.drawBitmap(6, 17, image_Layer_9__copy__bits, 4, 4, 1);
 
     display.drawBitmap(82, 2, image_Layer_11_bits, 12, 20, 1);
 
     display.drawBitmap(8, 22, image_Layer_9__copy__bits, 4, 4, 1);
 
     display.drawBitmap(20, 21, image_Layer_9__copy__bits, 4, 4, 1);
 
     display.drawBitmap(0, 18, image_Layer_9__copy__bits, 4, 4, 1);
 
     display.drawBitmap(102, 0, image_Layer_17_bits, 26, 26, 1);
 }

 void cuideDasPlantas(void) {
    display.clearDisplay();

    display.drawBitmap(93, 16, image_FaceNopower_bits, 29, 14, 1);

    display.setTextColor(1);
    display.setTextSize(2);
    display.setTextWrap(false);
    display.setCursor(0, 0);
    display.print("CUIDE DAS");

    display.setCursor(0, 18);
    display.print("PLANTAS");
 }
 
 
static const unsigned char PROGMEM image_Layer_5_bits[] = {0xc0,0x00,0x40,0x00,0x48,0xa2,0x48,0x94,0x48,0x88,0x49,0x94,0x66,0xa2};

void displayLightSensor(void) {
    display.clearDisplay();

    // Safely read the light level
    float currentLight;
    if (xSemaphoreTake(lightMutex, portMAX_DELAY) == pdTRUE) {
        currentLight = lightLevel;
        xSemaphoreGive(lightMutex);
    } else {
        currentLight = 0.0; // Default if mutex fails
    }

    // Convert to integer and split into parts
    int value = static_cast<int>(currentLight);
    int first_part = (value >= 1000) ? (value / 1000) : 0;
    int second_part = value % 1000;

    // Format first part (2 digits)
    String first_str = (first_part < 10) ? "0" + String(first_part) : String(first_part);

    // Format second part (3 digits with leading zeros)
    String second_str = String(second_part);
    while (second_str.length() < 3) {
        second_str = "0" + second_str;
    }

    // Display settings
    display.setTextColor(1);      // White text
    display.setTextSize(2);       // Size 2 for readability
    display.setTextWrap(false);   // No wrapping

    // Print first part at (35, 0)
    display.setCursor(35, 0);
    display.print(first_str);

    // Print second part at (59, 7)
    display.setCursor(59, 7);
    display.setTextSize(1);
    display.print(second_str);

    // Optional: Add label
    display.setTextSize(1);
    display.setCursor(30, 16);
    display.print("LUZ AMBIENTE");

    // Optional: Add bitmap (adjust as needed)
    display.drawBitmap(80, 7, image_Layer_5_bits, 15, 7, 1);

    display.display(); // Update the display
}

void displaySoilSensors (void) {
    display.clearDisplay();

    // Read moisture levels from all sensors
    float moisture1 = MoistureSensorUtil::getMoisturePercentage(MoistureSensorUtil::SENSOR_1);
    float moisture2 = MoistureSensorUtil::getMoisturePercentage(MoistureSensorUtil::SENSOR_2);
    float moisture3 = MoistureSensorUtil::getMoisturePercentage(MoistureSensorUtil::SENSOR_3);

    // Display settings
    display.setTextColor(1);      // White text
    display.setTextSize(2);
    display.setTextWrap(false);   // No wrapping

    // Print moisture levels at specified positions
    display.setTextSize(1);
    display.setCursor(21, 17);
    display.print("H1");
    display.setTextSize(2);
    display.setCursor(15, 00);
    display.print(moisture1, 0);

    // Print moisture levels at specified positions
    display.setTextSize(1);
    display.setCursor(59, 17);
    display.print("H2");
    display.setTextSize(2);
    display.setCursor(53, 00);
    display.print(moisture2, 0);

    // Print moisture levels at specified positions
    display.setTextSize(1);
    display.setCursor(96, 17);
    display.print("H3");
    display.setTextSize(2);
    display.setCursor(91, 00);
    display.print(moisture3, 0);

    display.display(); // Update the display
}