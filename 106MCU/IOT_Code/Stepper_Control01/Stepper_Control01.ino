
#include <AccelStepper.h>
#define Steppin 8
#define Directionpin 9
#define Stoppin 10
int flag = 0 ;
// Define a stepper and the pins it will use
//AccelStepper stepper; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
//AccelStepper mystepper(1, Steppin, Directionpin,Stoppin );
AccelStepper mystepper(1,8,9,10 );
void setup()
{  
  Serial.begin(9600) ;
  Serial.println("now Start") ;
  mystepper.setMaxSpeed(500);
  mystepper.setSpeed(50);
 // mystepper.setAcceleration(100) ;
      Serial.print("Now pos is :(");
      Serial.print(mystepper.currentPosition());
      Serial.print(")\n");
      
  if (mystepper.currentPosition() != 0)
          mystepper.setCurrentPosition(0) ;

      //mystepper.move(2000);
}

void loop()
{
  
    if (flag == 0 )
      {
          if (mystepper.distanceToGo() <=0)
            {
              flag = 1;
                mystepper.moveTo(2000);
            }
      }
      else
      {
          if (mystepper.distanceToGo() <=0)
            {
                mystepper.moveTo(-2000);
                 flag = 0;
            }
      }
      
      mystepper.run();
      Serial.print("Now pos is :(");
      Serial.print(mystepper.distanceToGo());
      Serial.print("/");
      Serial.print(mystepper.currentPosition());
      Serial.print(")\n");
     // delay(50) ;
}
