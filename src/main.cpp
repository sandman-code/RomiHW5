#include <Arduino.h>
#include "Chassis.h"

enum States
{
  Start,
  Driving,
  Turning
} state;

Chassis chassis;

void setup()
{
  state = Start;
}

void loop()
{

  switch (state)
  {
  case Start:
    chassis.driveDistance(12);
    state = Driving;
    break;
  case Driving:

    break;
  case Turning:
    break;
  }