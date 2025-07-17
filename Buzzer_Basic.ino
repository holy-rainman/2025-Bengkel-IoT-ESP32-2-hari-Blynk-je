#define ledR(x) digitalWrite(14,x? HIGH:LOW)
#define ledY(x) digitalWrite(12,x? HIGH:LOW)
#define ledG(x) digitalWrite(13,x? HIGH:LOW)
#define buzz(x) digitalWrite(27,x? HIGH:LOW)

int led[4]={18, 19, 23, 5};

void setup() 
{ for(int i=0 ;i<=3 ;i++) pinMode(led[i],OUTPUT);
  for(int i=12;i<=14;i++) pinMode(i,OUTPUT);
  pinMode(27,OUTPUT);
  buzz(1);  delay(100);
  buzz(0);
}

void loop() 
{ for(uint8_t i=0;i<3;i++)
  { digitalWrite(led[0],HIGH);  delay(500);
    digitalWrite(led[0],LOW);   delay(500);
  }
 
  while(1)
  { digitalWrite(led[1],HIGH);  delay(200);
    digitalWrite(led[1],LOW);   delay(200);
  } 
}

void trafficLight()
{ ledY(0);  ledR(1);  delay(3000);
  ledR(0);  ledG(1);  delay(3000);
  ledG(0);  ledY(1);  delay(2000);
}

