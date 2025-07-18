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
uint8_t cnt=0;
void loop() 
{ sprintf(txt,"PB1:%d PB2:%d",pb1,pb2);
  Serial.println(txt);
 
  if(pb1==0)
  { digitalWrite(led[0],HIGH); digitalWrite(led[1],LOW);
    digitalWrite(led[2],HIGH); digitalWrite(led[3],LOW);
  }
  if(pb2==1)
  { digitalWrite(led[0],LOW); digitalWrite(led[1],HIGH);
    digitalWrite(led[2],LOW); digitalWrite(led[3],HIGH);
  }
  if(pb1==1 && pb2==0)
  { for(uint8_t i=0;i<4;i++) digitalWrite(led[i],HIGH);
    delay(100); 
    for(uint8_t i=0;i<4;i++) digitalWrite(led[i],LOW);
    delay(100); 
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
