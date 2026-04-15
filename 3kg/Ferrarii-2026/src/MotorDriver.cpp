#include "MotorDriver.hpp"

MotorDriver::MotorDriver() {
    leftSpeed = 0;
    rightSpeed = 0;
    leftDirection = FORWARD;
    rightDirection = FORWARD;
    isBraking = false;
}

void MotorDriver::setSpeed(int _leftSpeed, int _rightSpeed) {
    leftSpeed = _leftSpeed;
    rightSpeed = _rightSpeed;
}

void MotorDriver::setDirection(Direction _leftDirection, Direction _rightDirection) {
    leftDirection = _leftDirection;
    rightDirection = _rightDirection;
}

void MotorDriver::setIsBraking(bool _isBraking) {
    isBraking = _isBraking;
}

bool MotorDriver::getIsBraking() {
    return isBraking;
}

int MotorDriver::getLeftSpeed() {
    return leftSpeed;
}

int MotorDriver::getRightSpeed() {
    return rightSpeed;
}

Direction MotorDriver::getLeftDirection() {
    return leftDirection;
}

Direction MotorDriver::getRightDirection() {
    return rightDirection;
}
