#include "Arduino.h"
#include "BlueMotor.h"

long count = 0;
int errorCount = 0;
const char X = 5;

char encoderArray[4][4] = {
    {0, -1, 1, X},
    {1, 0, X, -1},
    {-1, X, 0, 1},
    {X, 1, -1, 0}};

void BlueMotor::setup()
{

    pinMode(0, INPUT);
    pinMode(1, INPUT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(2), isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), isr, CHANGE);
    pinMode(PWMOutPin, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);
}

void BlueMotor::setEffort(int effort, bool clockwise)
{
    if (clockwise)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }
    int value = constrain(effort, 0, 400);
    OCR1C = value;
}

void BlueMotor::setEffort(int effort)
{
    if (effort < 0)
    {
        setEffort(-effort, true);
    }
    else
    {
        setEffort(effort, false);
    }
}

long BlueMotor::getPosition()
{
    isr();
    return count;
}

void BlueMotor::reset()
{
    isr();
    count = 0;
}

void isr()
{

    char oldValue = digitalRead(3);
    char newValue = (digitalRead(3) << 1) | digitalRead(2);
    char value = encoderArray[oldValue][newValue];
    if (value == X)
    {
        errorCount++;
    }
    else
    {
        count -= value;
    }
    oldValue = newValue;
}