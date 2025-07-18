#define ledR(x) digitalWrite(14,x? HIGH:LOW)
#define ledY(x) digitalWrite(12,x? HIGH:LOW)
#define ledG(x) digitalWrite(13,x? HIGH:LOW)
#define buzz(x) digitalWrite(27,x? HIGH:LOW)
#define rly1(x) digitalWrite(16,x? LOW:HIGH)
#define rly2(x) digitalWrite(17,x? LOW:HIGH)
#define pb1 digitalRead(25)
#define pb2 digitalRead(26)
#define pot analogRead(34)
#define ldr analogRead(35)

int led[4]={18, 19, 23, 5};

void setup() 
{ for(int i=0 ;i<=3 ;i++) pinMode(led[i],OUTPUT);
  for(int i=12;i<=14;i++) pinMode(i,OUTPUT);
  pinMode(27,OUTPUT);
  pinMode(16,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(25,INPUT_PULLUP);
  pinMode(26,INPUT_PULLDOWN);

  Serial.begin(9600);
  rly1(0);  rly2(0);  //RELAY BOTH OFF
  beep(3,50);
}

uint16_t smoothingAnalogValue(uint8_t pin, uint8_t samples = 10) 
{ uint32_t sum = 0;
  for(uint8_t i = 0; i < samples; i++) 
  { sum += analogRead(pin);
    delay(2); 
  }
  return sum / samples;
}

char txt[100];
uint8_t cnt=0;
void loop() 
{ uint16_t an = smoothingAnalogValue(34);
  float volt = (float)an/4095*3.3;
  uint8_t anMAP = map(an,0,4095,0,4);
  uint16_t anLDR = smoothingAnalogValue(35); 
  
  sprintf(txt,"ADC:%d, Volt:%.2fV, LDR:%d",an,volt,anLDR);
  Serial.println(txt);

  for(uint8_t i=0;i<4;i++)
    digitalWrite(led[i], i<anMAP? HIGH:LOW);
}

void checkCnt()
{ if(cnt==1)  digitalWrite(led[0],HIGH);
  if(cnt==2)  digitalWrite(led[1],HIGH);
  if(cnt==3)  digitalWrite(led[2],HIGH);
  if(cnt==4)  digitalWrite(led[3],HIGH);
  if(cnt==5)  
  { cnt=0;
    beep(2,50);
    for(uint8_t i=0;i<4;i++)
      digitalWrite(led[i],LOW);
  }
  return;
}

void beep(uint8_t bil, uint16_t tempoh)
{ for(uint8_t i=0;i<bil;i++)
  { buzz(1);  delay(tempoh);
    buzz(0);  delay(tempoh);
  }
}

void trafficLight()
{ ledY(0);  ledR(1);  delay(3000);
  ledR(0);  ledG(1);  delay(3000);
  ledG(0);  ledY(1);  delay(2000);
}
