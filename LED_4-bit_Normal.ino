int led1=18, led2=19, led3=23, led4=5;

void setup() 
{ pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);     
}

void loop() 
{ digitalWrite(led1, HIGH);   
  digitalWrite(led2, HIGH);   
  digitalWrite(led3, HIGH);   
  digitalWrite(led4, HIGH); delay(1000);                     
  digitalWrite(led1, LOW);  
  digitalWrite(led2, LOW);  
  digitalWrite(led3, LOW);  
  digitalWrite(led4, LOW);  delay(1000);                      
}
