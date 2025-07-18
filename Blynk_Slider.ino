#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

uint8_t LEDs[]={18,19,23,5};

BLYNK_CONNECTED()
{ Blynk.virtualWrite(V0,LOW);
  Blynk.virtualWrite(V1,LOW);
}
BLYNK_WRITE(V0)
{ uint8_t led=param.asInt();
  digitalWrite(LEDs[0],led);
}
BLYNK_WRITE(V1)
{ uint8_t pwm = param.asInt();
  pwm = pwm*255/100;
  Serial.println(pwm);
  analogWrite(LEDs[1],pwm);
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
