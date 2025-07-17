int led[4]={18, 19, 23, 5};

void setup() 
{ for(int i=0;i<=3;i++)
    pinMode(led[i],OUTPUT);
}

void loop() 
{ for(int i=0;i<=3;i++) digitalWrite(led[i],HIGH); 
  delay(1000);                     
  for(int i=0;i<=3;i++) digitalWrite(led[i],LOW); 
  delay(1000);                                         
}

