#include "Bluemotor.h"
#include <Romi32U4.h>
// variables for the counter of controlling the encoder
const char X = 5;
int errorCount = 0;
int oldValue = 0;
long count = 0;
char encoderArray[4][4] = {
    {0, 1, -1, X},
    {-1, 0, X, 0},
    {1, X, 0, -1},
    {X, -1, 1, 0}};
// the differnt sates for the move to function
enum States
{
    Start,
    clockwise,
    counterclockwise,
    stop
} state;

//initilizes all the pins and the interupts
void Bluemotor::initilize()
{ //outputs and inputs to controller the blue motor
    pinMode(PWM, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(ENCA, INPUT);
    pinMode(ENCB, INPUT);
    motors.setEfforts(0, 0);

    //interupts to count the encoder
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    attachInterrupt(digitalPinToInterrupt(0), isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(1), isr, CHANGE);

    //initlize the differnt states
    state = Start;
};

//The intrupt service routune
void Bluemotor::isr()
{ //shifts the bits left deping on the reading of the second pin, looks up the value in the array
    int newValue = (digitalRead(1) << 1) | digitalRead(0);
    char value = encoderArray[oldValue][newValue];

    //if the number changed add or subtract, or if the value did not change add add one to errorcount
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

//will change the mover the motor clockwiseor counterclockwise and adjust the speed
void Bluemotor::setEffort(int effort, bool clockwise)
{
    //turn clockwise
    if (clockwise)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
    }

    //do not turn
    else if (effort == 0)
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
    }

    //turn counter clockwise
    else
    {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
    }

    //validaadates the effort number and sends a PWM to the motor
    int value = constrain(effort, 0, 400);
    OCR1C = value;
}

//sorts the inital effort for direction and speed
void Bluemotor::setEffort(int effort)
{

    //turn clockwise
    if (effort < 0)
    {
        setEffort(-effort, true);
    }
    //turn counterclockwise or stop
    else
    {
        setEffort(effort, false);
    }
}

//reports back the position of the motor
long Bluemotor::getPosition()
{
    return count;
}

//resets the position count of the encouder to count that as the new base position
void Bluemotor::reset()
{
    count = 0;
}

//moves the mover a certion amount depening on the position input
void Bluemotor::moveTo(long position)
{ //initlizes a Bluemotor varabvle and grabs the current posiotn of the encoder
    Bluemotor blue;
    noInterrupts();
    long spot = blue.getPosition();
    interrupts();

    //all the cases for the moving the motor
    switch (state)
    {
        //initally moves the motor clockwise our counter clockwise
    case Start:
        //moves the motor clockwise
        if (position > 0)
        {
            blue.setEffort(-200);
            state = clockwise;
        }

        //moves the motor counterclockwise
        else
        {
            blue.setEffort(200);
            state = counterclockwise;
        }
        //reset the encoder position
        blue.reset();
        spot = blue.getPosition();
        break;

        //if the motor reached its position will call stop
    case clockwise:
        if (spot >= position)
        {
            state = stop;
        }
        break;
    case counterclockwise:
        if (spot <= position)
        {
            state = stop;
        }
        break;

        //stops the motor and prepares the function if called again
    case stop:
        blue.setEffort(0);
        blue.reset();
        state = Start;
    }
}
