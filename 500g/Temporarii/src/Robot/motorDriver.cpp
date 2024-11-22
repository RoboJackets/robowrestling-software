#include "Robot/motorDriver.hpp"

// type | Class Name | function name
bool MotorDriver::getDirection() {
    return direction;
}
int MotorDriver::getSpeed() {
    return speed;
}
int MotorDriver::getValue() {
    return value;
}
void MotorDriver::setDirection(bool value) {
    direction = value;
}
void MotorDriver::setSpeed(int value) {
    speed = value;
}
void MotorDriver::setValue(int value) {
    this->value = value;
}