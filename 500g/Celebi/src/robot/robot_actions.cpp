#include "robot/robot_actions.hpp"
#include <Arduino.h>

robot_actions :: robot_actions(int* motors) {
    this -> motors = motors;
    acceleration = 5;
}

void robot_actions :: brake() {
    motors[0] = 0;
    motors[1] = 0;
}

void robot_actions :: drive_forward(int speed) {
    // cap speed increase to acceleration
    if (speed - motors[0] > acceleration || speed - motors[1] > acceleration) {
        motors[0] += acceleration;
        motors[1] += acceleration;
    } else {
        motors[0] = speed;
        motors[1] = speed;
    }
}

void robot_actions :: drive_backward(int speed) {
    motors[0] = -1 * speed;
    motors[1] = -1 * speed;
}

void robot_actions :: turn_left(int speed) {
    motors[0] = -1 * speed;
    motors[1] = speed;
}

void robot_actions :: turn_right(int speed) {
    motors[0] = speed;
    motors[1] = -1 * speed;
}

void robot_actions :: drive_custom(int LSpeed, int RSpeed, bool LDir, bool RDir) {
    // cap speed increase to acceleration
    if (LSpeed - motors[0] > acceleration) {
        motors[0] += acceleration;
    } else if (RSpeed - motors[1] > acceleration) {
        motors[1] += acceleration;
    } else {
        motors[0] = LDir * LSpeed;
        motors[1] = RDir * RSpeed;
    }
}