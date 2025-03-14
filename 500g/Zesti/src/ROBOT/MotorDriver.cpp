#include "include/ROBOT/MotorDriver.h"

int MotorDriver::getSpeed() {
    return speed;
}

bool MotorDriver::getDirection() {
    return direction;
}

void MotorDriver::setSpeed(int speedInput) {
    speed = speedInput;
}

void MotorDriver::setDirection(bool directionInput) {
    direction = directionInput;
}

/**
 * Checked and Verified by: Braiden Anderson
 */