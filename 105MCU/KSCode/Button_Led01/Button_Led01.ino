void setup() {
  // put your setup code here, to run once:
      pinMode(13,OUTPUT) ;
      pinMode(7,INPUT);
      
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(13,HIGH);
      delay(2000) ;
   digitalWrite(13,LOW);
      delay(3000) ;
}