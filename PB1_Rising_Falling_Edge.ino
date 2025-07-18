#define ledR(x) digitalWrite(14,x? HIGH:LOW)
#define ledY(x) digitalWrite(12,x? HIGH:LOW)
#define ledG(x) digitalWrite(13,x? HIGH:LOW)
#define buzz(x) digitalWrite(27,x? HIGH:LOW)
#define rly1(x) digitalWrite(16,x? LOW:HIGH)
#define rly2(x) digitalWrite(17,x? LOW:HIGH)
#define pb1 digitalRead(25)
#define pb2 digitalRead(26)

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

char txt[100];
void loop() 
{ if(PB1==0)
  { LEDR(1);  delay(500);
    while(PB1==0)
    { LEDY(1);
      LEDR(0);
    }
    LEDG(1);  LEDY(0);  delay(500);
    LEDG(0);
  }
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
