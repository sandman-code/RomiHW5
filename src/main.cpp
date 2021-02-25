#include <Arduino.h>
#include "Chassis.h"
#include 

Chassis chassis;

enum States
{
  Start,
  Driving,
  Turning
} state;

void doDriving()
{
  switch (state)
  {
      case Start:
          chassis.driveDistance(12);
          state = Driving;
          break;

      case Driving:
          chassis.driveDistance(12);
          if(chassis.doneDriving())
          {
            state = Turning;
          }  
          break;

      case Turning:
          chassis.turnAngle(90);
          if(chassis.doneDriving())
          {
            state = Driving;
          }
          break;
    }
}

void setup()
{
  state = Start;
}

void loop()
{
  doDriving();
  
}