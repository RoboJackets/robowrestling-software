#include "include/MotorDriver.h"

MotorDriver::MotorDriver() {

}

MotorDriver::MotorDriver(int speedInput, bool directionInput) {
    speed = speedInput;
    direction = directionInput;
}

int MotorDriver::getSpeed() {
    return speed;
}

bool MotorDriver::getDirection() {
    return direction;
}

void MotorDriver::setSpeed(int speedInput) {
    speedInput = speed;
}

void MotorDriver::setDirection(bool directionInput) {
    direction = directionInput;
}

