#ifndef MOTOR_ACTIONS_H
#define MOTOR_ACTIONS_H
#include "timer.hpp"

class motor_actions {
    private:
        int* motors;
        int* ir_sensors;
        timer* actionTimer;
        bool seeThing = true;
        bool lastSawThing = true;
    public:
        motor_actions(int* motors, int* sensors, timer* actionTimer);
        void drive_binary();
        void drive_avgs(float* avgs);
        void driveForward(int speed); 
        void driveBackward(int speed); 
        void spinLeft(int speed); 
        void spinRight(int speed); 
        void stop();
        void customDrive(int rightSpeed, int leftSpeed);
};

#endif