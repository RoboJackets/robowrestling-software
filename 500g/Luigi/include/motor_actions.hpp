#ifndef MOTOR_ACTIONS_H
#define MOTOR_ACTIONS_H
#include "timer.hpp"

class motor_actions {
    private:
        int* motors;
    public:
        motor_actions(int* motors);
        void driveForward(int speed); 
        void driveBackward(int speed); 
        void spinLeft(int speed); 
        void spinRight(int speed); 
        void stop();
        void customDrive(int rightSpeed, int leftSpeed);
};

#endif