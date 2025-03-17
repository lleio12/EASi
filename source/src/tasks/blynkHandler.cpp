#include "blynkConfig.h" // Include Blynk definitions
#include "tasks/blynkHandler.h"

// Define your WiFi credentials
char ssid[] = "Nigga Shark";
char pass[] = "nigger69";

#define RELAY_PIN 3

void setup() {
    // Initialize Blynk with the auth token from blynkConfig.h
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

    // Set the relay pin as output
    pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
    // Run Blynk
    Blynk.run();
}

// Blynk virtual pin write handler
BLYNK_WRITE(V1) {
    int pinValue = param.asInt(); // Get the value from the Blynk app
    digitalWrite(RELAY_PIN, pinValue); // Control the relay
}