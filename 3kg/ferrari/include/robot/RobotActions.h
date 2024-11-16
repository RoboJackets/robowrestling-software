#ifndef ROBOT_ACTIONS_H
#define ROBOT_ACTIONS_H
#include "motor-driver/MotorDriver.h"
class RobotActions {
    //figure out motor driver stuff
    private:
        MotorDriver* leftMotor;
        MotorDriver* rightMotor;
    public:
        RobotActions(MotorDriver* leftMotor, MotorDriver* rightMotor);
        void brake();
        void driveForward(int speed);
        void driveBackward(int speed); 
        void turnRight(int speed); 
        void turnLeft(int speed); 
};
#endif