#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;

#include <dhtESP32-rmt.h>
float temperature = 0.0;
float humidity = 0.0;

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
bool status=0;
void kelip()
{ digitalWrite(LEDs[2],status);
  status=!status;
}
void getADC()
{ uint16_t an = analogRead(34);
  an = map(an,0,4095,1,10);
  Blynk.virtualWrite(V2,an);
}
char txt[100];
void getDHT()
{ uint8_t error=read_dht(temperature, humidity, 4, DHT11);
	if(error)
		Serial.println(error);
	else
	{	sprintf(txt,"Temperature:%.1fC, Humidity:%.1f%%",temperature,humidity);
    Serial.println(txt);
    Blynk.virtualWrite(V3,temperature);
    Blynk.virtualWrite(V4,humidity);
	}
}

void setup()
{ for(uint8_t i=0;i<4;i++)
    pinMode(LEDs[i],OUTPUT);
  
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200L,kelip);
  timer.setInterval(10L,getADC);
  timer.setInterval(2000L,getDHT);
}

void loop()
{ Blynk.run();
  timer.run();
}
