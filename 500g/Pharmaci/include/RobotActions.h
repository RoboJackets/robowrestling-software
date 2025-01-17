#ifndef ROBOT_ACTIONS_H
#define ROBOT_ACTIONS_H

#include "MotorDriver.h"

class RobotActions {
    private:
        MotorDriver *leftMotorDriver;
        MotorDriver *rightMotorDriver;
    public:
        RobotActions(MotorDriver *leftMotorDriverPointer, MotorDriver *rightMotorDriverPointer);
        void drive(int leftSpeed, int rightSpeed);
};

#endif