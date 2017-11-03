//  this code is only for arduino pro micro or arduino micro 
#include <Keyboard.h>
boolean RA_Key, RB_Key, RD_Key;
unsigned char Button_Times = 0xFF;
unsigned char Last_Button_Times = Button_Times;
char Bnumber=0;

void setup() {
  pinMode(17, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(5, INPUT);
  Serial.begin(9600);
  //while(!Serial) ;
  Keyboard.begin();
  Serial.println("The program start up...");
}

void loop() {

 RA_Key=digitalRead(2);
 RB_Key=digitalRead(3);
 RD_Key=digitalRead(5);
 if(RA_Key) {
    delay(10);
    Bnumber=1;Button_Times=0x01; }   
  else if(RB_Key) {
    delay(10);
    Bnumber=2;Button_Times=0x02; }
  else if(RD_Key) {
    delay(10);
    Bnumber=3;Button_Times=0x03; }
  else {
    delay(10);
    Bnumber=99;Button_Times=0xFF;
    digitalWrite(17, HIGH); //low active
    }
    
  if(Button_Times != Last_Button_Times) {
    Last_Button_Times=Button_Times;
    switch(Bnumber) {
      case 1:
        digitalWrite(17, LOW); //low active
        Keyboard.press(KEY_RIGHT_ARROW);
        delay(10);
        Keyboard.releaseAll();
        break;
      case 2:
        digitalWrite(17, LOW); //low active
        Keyboard.press(KEY_LEFT_ARROW);
        delay(10);
        Keyboard.releaseAll();
        break;
      case 3:
        digitalWrite(17, LOW); //low active
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_F5);
        delay(10);
        Keyboard.releaseAll();
        Keyboard.press(KEY_HOME);
        delay(10);
        Keyboard.releaseAll();
        break;
      }
    }
  
}

