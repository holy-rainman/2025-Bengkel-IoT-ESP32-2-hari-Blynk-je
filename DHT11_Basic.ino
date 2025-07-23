#include <dhtESP32-rmt.h>
float temperature = 0.0;
float humidity = 0.0;

void setup() 
{ delay(1000);
	Serial.begin(9600);
}

void loop() 
{	uint8_t error=read_dht(temperature, humidity, 4, DHT11);
	if(error)
		Serial.println(error);
	else
	{	Serial.print("Temperature: ");  Serial.print(temperature);
		Serial.print("  Humidity: ");   Serial.println(humidity);
	}
	delay(3000);	
}
