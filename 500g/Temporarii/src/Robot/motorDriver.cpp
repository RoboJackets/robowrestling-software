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
    direction = value;
}
void MotorDriver::setSpeed(int value) {
    speed = value;
}