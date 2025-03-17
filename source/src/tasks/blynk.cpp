#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL5i2z9CRPw"
#define BLYNK_TEMPLATE_NAME         "EASI"
#define BLYNK_AUTH_TOKEN            "Iq2gtah4aNJB_ZyzkLsuoTblYGN4kIFu"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Nigga Shark";
char pass[] = "nigger69";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}
