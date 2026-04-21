#include "robot/robot_actions.hpp"
#include <Arduino.h>

robot_actions :: robot_actions(int16_t* motors) {
    this->motors = motors;
}

void robot_actions :: brake() {
    motors[0] = 0;
    motors[1] = 0;
}

void robot_actions :: drive_forward(uint8_t speed) {
    motors[0] = speed;
    motors[1] = speed;
}

void robot_actions :: drive_backward(uint8_t speed) {
    motors[0] = -1 * speed;
    motors[1] = -1 * speed;
}

void robot_actions :: turn_left(uint8_t speed) {
    motors[0] = -1 * speed;
    motors[1] = speed;
}

void robot_actions :: turn_right(uint8_t speed) {
    motors[0] = speed;
    motors[1] = -1 * speed;
}

void robot_actions :: drive_custom(uint8_t LSpeed, uint8_t RSpeed, bool LDir, bool RDir) {
    motors[0] = LDir * LSpeed;
    motors[1] = RDir * RSpeed;
}