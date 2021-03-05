#include <Bluemotor.h>
#include <Arduino.h>
#include <Romi32U4.h>
Romi32U4ButtonB pb;

Romi32U4Motors motors;

Bluemotor motor;
long oldReading = 0;
long newReading = 0;
long old = 0;
unsigned long time = 5;
float newt = 0;
long freq = 0;

void setup()
{
  Serial.begin(9600);
  motor.initilize(); // put your setup code here, to run once:
}

void loop()
{
  if (pb.isPressed())
  {
    newt = millis() / 1000;
    newReading = motor.getPosition();
    freq = (newReading - oldReading) / (newt - old);
    unsigned long endTime = millis() + 100;
    motor.setEffort(400); // effort test value
    Serial.println(motor.getPosition());
    Serial.println(millis());
    Serial.println((freq * 60) / 540);
    Serial.println();
    while (millis() < endTime)
      ;
  }
  else
  {
    old = millis() / 1000;
    oldReading = motor.getPosition();
    motor.setEffort(0);
    motor.reset();
  }
}