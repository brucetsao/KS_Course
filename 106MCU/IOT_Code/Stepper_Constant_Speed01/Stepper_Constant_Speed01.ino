// Random.pde
// -*- mode: C++ -*-
//
// Make a single stepper perform random changes in speed, position and acceleration
//
// Copyright (C) 2009 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $
#include <AccelStepper.h>
// Define a stepper and the pins it will use
//AccelStepper stepper; // Defaults to AccelStepper::
AccelStepper stepper(1,8,9,10 );
void setup()
{
  stepper.setMaxSpeed(500);  
}
void loop()
{
    if (stepper.distanceToGo() == 0)
    {
        // Random change to speed, position and acceleration
        // Make sure we dont get 0 speed or accelerations
        delay(1000);
        stepper.moveTo(rand() % 5000);
       // stepper.setMaxSpeed((rand() % 200) + 1);
        //stepper.setAcceleration((rand() % 200) + 1);
        stepper.setAcceleration(300) ;
    }
    stepper.setSpeed(1000) ;
    stepper.runSpeed();
}
