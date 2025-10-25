#include "MotorDriver.hpp"

MotorDriver::MotorDriver() {
    acclerationTimer = new Timer(ACCELERATION_INTERVAL);
    leftDirectionTimer = new Timer(LEFT_DIRECTION_CHANGE_TIMER_DURATION, true);
    rightDirectionTimer = new Timer(RIGHT_DIRECTION_CHANGE_TIMER_DURATION, true);
    leftSpeed = 0;
    rightSpeed = 0;
    leftTargetSpeed = 0;
    rightTargetSpeed = 0;
}

void MotorDriver::setSpeed(int _leftSpeed, int _rightSpeed) {
    if (!leftDirectionTimer->isReady()) {
        leftSpeed = 0;
    } else {
        leftSpeed = _leftSpeed;
    }
    if (!rightDirectionTimer->isReady()) {
        rightSpeed = 0;
    } else {
        rightSpeed = _rightSpeed;
    }
}

void MotorDriver::setDirection(Direction _leftDirection, Direction _rightDirection) {
    if (_leftDirection != leftDirection) {
        leftDirectionTimer->resetTimer();
    }
    if (_rightDirection != rightDirection) {
        rightDirectionTimer->resetTimer();
    }
    leftDirection = _leftDirection;
    rightDirection = _rightDirection;
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
