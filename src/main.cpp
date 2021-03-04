#include <Bluemotor.h>
#include <Arduino.h>
#include <Romi32U4.h>
Romi32U4ButtonB pb;

Romi32U4Motors motors;

Bluemotor motor;
long reading = 0;
long old = 0;
unsigned long time = 5;
float newt = 0;
void setup()
{
  Serial.begin(9600);
  motor.initilize(); // put your setup code here, to run once:
}

void loop()
{
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