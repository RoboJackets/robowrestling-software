#ifndef ROBOTACTIONS_H
#define ROBOTACTIONS_H

#include "world_state.hpp"
#include "algorithms.hpp"

class robot_actions {
    private:
        int* motors;
        const int rightPWM = 6;
        const int rightDIR = 5;
        const int leftPWM = 8;
        const int leftDIR = 7;
    public:
        robot_actions(int* motor_vals);
        void applyMotors();
        void brake();
        void drive_forward(int speed);
        void drive_backward(int speed);
        void drive_right(int speed);
        void drive_left(int speed);
};

#endif