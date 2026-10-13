#include "MotorDriver.hpp"

MotorDriver::MotorDriver() {
    leftSpeed = 0;
    rightSpeed = 0;
    leftDirection = FORWARD;
    rightDirection = FORWARD;
    isBraking = false;
    left_direction_timer = new Timer(DIRECTION_TIMER_DURATION, true);
    right_direction_timer = new Timer(DIRECTION_TIMER_DURATION, true);
}

void MotorDriver::setSpeed(int _leftSpeed, int _rightSpeed) {
    leftSpeed = _leftSpeed;
    rightSpeed = _rightSpeed;
}

void MotorDriver::setDirection(Direction _leftDirection, Direction _rightDirection) {
    if (leftDirection != _leftDirection && left_direction_timer->isReady()) {
        leftDirection = _leftDirection;
        left_direction_timer->resetTimer();
    }
    if (rightDirection != _rightDirection && right_direction_timer->isReady()) {
        rightDirection = _rightDirection; 
        right_direction_timer->resetTimer();
    }
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
