#ifndef ROBOTACTION_H
#define ROBOTACTION_H

#include "MotorDriver.h"

class RobotAction {
private:
    MotorDriver *leftMotorDriver;
    MotorDriver *rightMotorDriver;
    int speed;
public:
    RobotAction(MotorDriver *leftMotorDriverPointer, MotorDriver *rightMotorDriverPointer, int speedValue);
    void setSpeed(int speedValue);
    void forward();
    void back();
    void spinLeft();
    void spinRight();
    void pivotLeft();
    void pivotRight();
    void slightTurnLeft();
    void brake();
};

#endif