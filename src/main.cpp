#include <Arduino.h>
#include "Chassis.h"
#include "Timer.h"
#include "IRdecoder.h"
#include "RemoteConstants.h"
#include "BlueMotor.h"

Chassis chassis;

Timer blinkingTimer(250);
IRDecoder decoder(14);
char lightOn = 0;
const float LED_PIN = 13;
Romi32U4ButtonA pb;
BlueMotor motor;

bool paused = false;

void doBlinking()
{
  if (blinkingTimer.isExpired())
  {
    lightOn = !lightOn;
    digitalWrite(LED_PIN, lightOn);
  }
}

void checkRemote()
{
  int16_t code = decoder.getKeyCode();
  switch (code)
  {
  case remoteVolMinus:
    paused = true;
    break;

  case remoteVolPlus:
    paused = false;
    break;
  }
}

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
    chassis.encoders.getCountsAndResetLeft();
    chassis.encoders.getCountsAndResetRight();
    chassis.driveDistance(12);
    state = Driving;
    break;

  case Driving:
    chassis.encoders.getCountsAndResetLeft();
    chassis.encoders.getCountsAndResetRight();
    if (paused)
    {
      chassis.pauseDriving();
    }
    else
    {
      chassis.resumeDriving();
    }
    if (chassis.doneDriving())
    {
      state = Turning;
    }
    chassis.driveDistance(12);
    break;

  case Turning:
    chassis.encoders.getCountsAndResetLeft();
    chassis.encoders.getCountsAndResetRight();
    if (paused)
    {
      chassis.pauseDriving();
    }
    else
    {
      chassis.resumeDriving();
    }
    if (chassis.doneDriving())
    {
      state = Driving;
    }
    chassis.turnAngle(90);
    break;
  }
}

void setup()
{
  state = Start;
}

void loop()
{
  //checkRemote();
  //doDriving();
  //doBlinking();
  if (pb.isPressed())
  {
    unsigned long endTime = millis() + 100;
    motor.setEffort(200); // effort test value
    Serial.println(motor.getPosition());
    while (millis() < endTime)
      ;
  }
  else
  {
    motor.setEffort(0);
    motor.reset();
  }
}