#include "MotorDriver.h"

MotorDriver::MotorDriver() {
    speed = 0;
    direction = 0;
}

int MotorDriver::getDirection() {
    return direction;
}

int MotorDriver::getSpeed() {
    return speed;
}

void MotorDriver::setDirection(int directionValue) {
    direction = directionValue;
}

void MotorDriver::setSpeed(int speedValue) {
    speed = speedValue;
}