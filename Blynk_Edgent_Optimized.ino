#define BLYNK_TEMPLATE_ID "TMPL6Ph6HH6_E"
#define BLYNK_TEMPLATE_NAME   "Latihan IoT"
#define BLYNK_FIRMWARE_VERSION  "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_ESP32_DEV_MODULE
#include <WiFi.h>
#include "BlynkEdgent.h"

void setup()
{ Serial.begin(9600);
  BlynkEdgent.begin();
}

void loop() 
{ BlynkEdgent.run();
}

