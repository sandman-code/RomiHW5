#include "Arduino.h"
#include "BlueMotor.h"

const char X = 5;

char encoderArray[4][4] = {    
    {0, -1, 1, X},    
    {1, 0, X, -1},    
    {-1, X, 0, 1},    
    {X, 1, -1, 0}};


void setup(){  

    pinMode(0, INPUT);  
    pinMode(1, INPUT);  
    Serial.begin(9600);  
    attachInterrupt(digitalPinToInterrupt(2), isr, CHANGE);  
    attachInterrupt(digitalPinToInterrupt(3), isr, CHANGE);    

}

void isr() {  
    
    newValue = (digitalRead(3) << 1) | digitalRead(2);
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