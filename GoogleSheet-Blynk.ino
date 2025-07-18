//========================================= BLYNK
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "YOUR_TEMPLATE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;

char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

//========================================= DHT11
#include <dhtESP32-rmt.h>
float temperature = 0.0;
float humidity = 0.0;

//========================================= GOOGLE SHEET
#include <Arduino.h>
#include <WiFi.h>
#include "time.h"
#include <ESP_Google_Sheet_Client.h>
#include <GS_SDHelper.h>

#define PROJECT_ID "YOUR_PROJET_ID"
#define CLIENT_EMAIL "YOUR_CLIENT_EMAIL"
const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY---_YOUR_PRIVATE_KEY_---END PRIVATE KEY-----\n";
const char spreadsheetId[] = "YOUR_SPREADSHEET_ID";

unsigned long lastTime = 0;  
unsigned long timerDelay = 3000;
void tokenStatusCallback(TokenInfo info);

const char* ntpServer = "pool.ntp.org";
unsigned long epochTime; 
unsigned long getTime() 
{ time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) 
  {
    return(0);
  }
  time(&now);
  return now;
}

//========================================= VARIABLES
uint8_t LEDs[]={18,19,23,5};

//========================================= FUNCTIONS
char dht11DataT[100], dht11DataH[100];
void getDHT11()
{ uint8_t error=read_dht(temperature, humidity, 4, DHT11);
	if(error)
		Serial.println(error);
	else
	{ Serial.print("Suhu: ");
		Serial.print(temperature);
		Serial.print(", Kelembapan:");
		Serial.println(humidity);
	}
}

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
void sendGoogleSheet()
{ bool ready=GSheet.ready();

  if(ready && millis() - lastTime > timerDelay)
  { lastTime = millis();
    FirebaseJson response;
    Serial.println("\nAppend spreadsheet values...");
    Serial.println("----------------------------");
    FirebaseJson valueRange;

    // New DHT11 sensor readings
    getDHT11();
    // Get timestamp
    epochTime = getTime();

    valueRange.add("majorDimension", "COLUMNS");
    valueRange.set("values/[0]/[0]", epochTime);
    valueRange.set("values/[1]/[0]", temperature);
    valueRange.set("values/[2]/[0]", humidity);
    // valueRange.set("values/[3]/[0]", pres);

    bool success = GSheet.values.append(&response /* returned response */, spreadsheetId /* spreadsheet Id to append */, "Sheet1!A1" /* range to append */, &valueRange /* data range to append */);
    if (success)
    { response.toString(Serial, true);
      valueRange.clear();
    }
    else
      Serial.println(GSheet.errorReason());
    
    Serial.println();
    Serial.println(ESP.getFreeHeap());
  }
}

void setup()
{ for(uint8_t i=0;i<4;i++)
    pinMode(LEDs[i],OUTPUT);
  
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(200L,kelip);
  timer.setInterval(10L,getADC);
  timer.setInterval(2000L,getDHT11);
  timer.setInterval(2000L,sendGoogleSheet);
  
  configTime(0, 0, ntpServer);
  GSheet.printf("ESP Google Sheet Client v%s\n\n", ESP_GOOGLE_SHEET_CLIENT_VERSION);
  
  GSheet.setTokenCallback(tokenStatusCallback);
  GSheet.setPrerefreshSeconds(10 * 60);
  GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

void loop()
{ Blynk.run();
  timer.run();
}

void tokenStatusCallback(TokenInfo info)
{ if (info.status == token_status_error)
  { GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    GSheet.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
  }
  else
    GSheet.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
}
