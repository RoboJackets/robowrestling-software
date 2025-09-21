#include "Robot/Robot_Actions.hpp"

RobotActions::RobotActions() {
    motors[0] = 0;
    motors[1] = 0;
}

void RobotActions::brake() {
    motors[0] = 0;
    motors[1] = 0;
}

void RobotActions::drive_forward(int speed) {
    motors[0] = speed;
    motors[1] = speed;
}

void RobotActions::drive_backward(int speed) {
    motors[0] = -speed;
    motors[1] = -speed;
}

void RobotActions::drive_left(int speed) {
    motors[0] = -speed;
    motors[1] = speed;
}

void RobotActions::drive_right(int speed) {
    motors[0] = speed;
    motors[1] = -speed;
}

int RobotActions::get_left_velocity() {
    return motors[0];
} 

int RobotActions::get_right_velocity() {
    return motors[1];
}
