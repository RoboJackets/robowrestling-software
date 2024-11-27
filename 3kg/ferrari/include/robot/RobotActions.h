#ifndef ROBOT_ACTIONS_H
#define ROBOT_ACTIONS_H

#include "motor-driver/MotorDriver.hpp"

class RobotActions {
    private:
        RoboClaw *motorDriver;
    public:
        RobotActions();
        void brake();
        void driveForward();
        void driveForward(int speed);
        void driveBackward(); 
        void driveBackward(int speed);
        void spinRight(); 
        void spinLeft(); 
        void turnRight(int turnSpeed);
        void turnLeft(int turnSpeed);
};
#endif