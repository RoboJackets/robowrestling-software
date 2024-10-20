#include "motorDriver.hpp"

// type | Class Name | function name
bool MotorDriver::getDirection() {
    return dir;
}
double MotorDriver::getSpeed() {
    return speed;
}
void MotorDriver::setDirection(bool direction) {
    dir = direction;
}
void MotorDriver::setSpeed(double spd) {
    speed = spd;
}