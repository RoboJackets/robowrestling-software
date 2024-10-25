#ifndef ROBOT_ACTIONS_H
#define ROBOT_ACTIONS_H

#include "motor_driver.hpp"

class robot_actions {
    private:
        motor_driver left_motor;
        motor_driver right_motor;
    public:
        robot_actions();
        robot_actions(motor_driver left, motor_driver right);
        void brake();
        void drive_forward(int speed);
        void drive_backward(int speed);
        void turn_left(int speed);
        void turn_right(int speed);
};

#endif