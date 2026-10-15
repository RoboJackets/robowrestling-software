#ifndef ROBOTACTIONS_H
#define ROBOTACTIONS_H

#include "MotorDriver.hpp"

class RobotActions {
    private:
        MotorDriver* motorDriver;
    public:
        RobotActions(MotorDriver* _motorDriver);
        void forward(int speed);
        void backward(int speed);
        void turnForward(int leftSpeed, int rightSpeed);
        void turnBackward(int leftSpeed, int rightSpeed);
        void spinLeft(int speed);
        void spinRight(int speed);
        void brake();
};

#endif