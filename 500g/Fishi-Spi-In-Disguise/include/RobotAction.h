#ifndef ROBOTACTION_H
#define ROBOTACTION_H

#include "MotorDriver.h"

class RobotAction {
private:
    MotorDriver *leftMotorDriver;
    MotorDriver *rightMotorDriver;
    int speed;
    void setIsBraking(bool isBraking);
public:
    RobotAction(MotorDriver *leftMotorDriverPointer, MotorDriver *rightMotorDriverPointer, int speedValue);
    void setSpeed(int speedValue);
    void forward();
    void forward(int _speed);
    void back();
    void back(int _speed);
    void turn(int leftSpeed, int rightSpeed);
    void turnBack(int leftSpeed, int rightSpeed);
    void spinLeft();
    void spinLeft(int _speed);
    void pivotLeft();
    void spinRight();
    void spinRight(int _speed);
    void pivotRight();
    void brake();
};

#endif