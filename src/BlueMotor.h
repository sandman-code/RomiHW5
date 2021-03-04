#pragma once

#include <Romi32U4.h>
#include <Romi32U4Encoders.h>

class Bluemotor
{
public:
    void initilize();
    void setEffort(int effort);
    void moveTo(long position);
    long getPosition();
    void reset();

    //Chassis();

private:
    Romi32U4Motors motors;
    void setEffort(int effort, bool clockwise);
    static void isr();
    const unsigned PWM = 11;
    const int AIN2 = 4;
    const int AIN1 = 13;
    const int ENCA = 0;
    const int ENCB = 1;
};
