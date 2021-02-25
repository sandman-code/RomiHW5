#include "Romi32U4.h"

class Chassis
{
public:
    void driveDistance(float inches);
    bool doneDriving();
    void turnAngle(float angle);
    void pauseDriving();
    void resumeDriving();
    void doDriving();
    float errCoeff = 0.05;
    Chassis();

private:
    Romi32U4Motors motors;
    Romi32U4Encoders encoders;
    int leftEffort, rightEffort;
    const unsigned CPR = 1440;
    const float wheelDiameter = 2.8;
    const float wheelTrack = 5.75;
    long targetCount;
};