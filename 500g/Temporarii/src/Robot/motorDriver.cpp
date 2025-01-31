#include "Robot/motorDriver.hpp"

// type | Class Name | function name
bool MotorDriver::getDirection() {
    return direction;
}
int MotorDriver::getSpeed() {
    return speed;
}
void MotorDriver::setDirection(bool value) {
    direction = value;
}
void MotorDriver::setSpeed(int value) {
    speed = value;
}