#include "robot/robot_actions.hpp"

robot_actions :: robot_actions() {
    left_motor = motor_driver();
    right_motor = motor_driver();
}

robot_actions :: robot_actions(motor_driver left, motor_driver right) {
    left_motor = left;
    right_motor = right;
}

void robot_actions :: brake() {
    left_motor.set_speed(0);
    right_motor.set_speed(0);
}

void robot_actions :: drive_forward(int speed) {
    left_motor.set_direction(true);
    right_motor.set_direction(true);
    left_motor.set_speed(speed);
    right_motor.set_speed(speed);
}

void robot_actions :: drive_backward(int speed) {
    left_motor.set_direction(false);
    right_motor.set_direction(false);
    left_motor.set_speed(speed);
    right_motor.set_speed(speed);
}

void robot_actions :: turn_left(int speed) {
    right_motor.set_direction(true);
    right_motor.set_speed(speed);
    left_motor.set_direction(false);
    left_motor.set_speed(speed);
}

void robot_actions :: turn_right(int speed) {
    left_motor.set_direction(true);
    left_motor.set_speed(speed);
    right_motor.set_direction(false);
    right_motor.set_speed(0);
}