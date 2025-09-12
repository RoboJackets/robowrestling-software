#include <MotorDriver.h>

MotorDriver::MotorDriver() {
    this->speed = 0.0;
    this->direction = true;
}

MotorDriver::MotorDriver(double speed, bool direction) {
    this->speed = speed;
    this->direction = direction;
}

void MotorDriver::setDirection(bool direction) {
    this->direction = direction;
}

void MotorDriver::setSpeed(double speed) {
    this->speed = speed;
}

bool MotorDriver::getDirection() {
    return direction;
}

double MotorDriver::getSpeed() {
    return speed;
}

