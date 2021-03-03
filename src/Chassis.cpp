#include "Chassis.h"

/*
 * Assume the robot drives about 12 inches / second* 
 * Take the number of inches, divide by 12 and drive that long 
 * 
 * */

Chassis::Chassis()
{

}

void Chassis::driveDistance(float inches)
{
    targetCount = (inches / (wheelDiameter * PI)) * CPR;
    int rightCount = encoders.getCountsRight();
    int leftCount = encoders.getCountsLeft();
    int err = rightCount - leftCount;
    rightEffort = 100 - (err * errCoeff);
    leftEffort = 100 - (err * errCoeff);
    motors.setEfforts(leftEffort, rightEffort);
}

/** 
 * * Assume the robot turns at about 180 degrees per second 
 * */

void Chassis::turnAngle(float degrees)
{
    targetCount = (((wheelTrack * PI * degrees) / 360) / (wheelDiameter * PI) * CPR);
    int rightCount = encoders.getCountsRight();
    int leftCount = encoders.getCountsLeft();
    int err = rightCount - leftCount;
    rightEffort = -100 - (err * errCoeff);
    leftEffort = 100 - (err * errCoeff);
    motors.setEfforts(leftEffort, rightEffort);
}

bool Chassis::doneDriving()
{
    return encoders.getCountsRight() < targetCount;
}

void Chassis::pauseDriving()
{
    motors.setEfforts(0, 0);
    digitalWrite(LED_PIN, 0);
}

void Chassis::resumeDriving()
{
    motors.setEfforts(leftEffort, rightEffort);
}
