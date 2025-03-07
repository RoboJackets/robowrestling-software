#include "Robot/motorDriver.hpp"

// type | Class Name | function name
MotorDriver::MotorDriver() {
    direction = 0;
    speed = 0;
}
int MotorDriver::getDirection() {
    return direction;
}
int MotorDriver::getSpeed() {
    return speed;
}
void MotorDriver::setDirection(int value) {
    if (value == 1) {
        direction = 1;
    } else {
        direction = 0;
    }
}
void MotorDriver::setSpeed(int value) {
    speed = value;
}