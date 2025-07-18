#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6Ph6HH6_E"
#define BLYNK_TEMPLATE_NAME "Latihan IoT"
#define BLYNK_AUTH_TOKEN "ozCIeidx7nX9VxJbYVYpF2XP5U7DX1wS"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "JHChua@unifi";
char pass[] = "adamdanial123";

uint8_t LEDs[]={18,19,23,5};

BLYNK_WRITE(V0)
{ uint8_t led=param.asInt();
  digitalWrite(LEDs[0],led);
}

void setup()
{ for(uint8_t i=0;i<4;i++)
    pinMode(LEDs[i],OUTPUT);
  
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{ Blynk.run();
}
