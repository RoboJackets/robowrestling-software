#include "MotorDriver.hpp"

MotorDriver::MotorDriver() {
    leftSpeed = 0;
    rightSpeed = 0;
    time_switched = 0;
    switched_count = 0;
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
    bool direction_switched = false;
    if (leftDirection != _leftDirection && left_direction_timer->isReady()) {
        leftDirection = _leftDirection;
        left_direction_timer->resetTimer();
        direction_switched = true;
    }
    if (rightDirection != _rightDirection && right_direction_timer->isReady()) {
        rightDirection = _rightDirection; 
        right_direction_timer->resetTimer();
        direction_switched = true;
    }
    if (direction_switched) {
        if (isSwitching10()) {
            setIsBraking(true);
        }
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

/**
 * returns True if the direction has switched 10 times in the last second. 
 */
bool MotorDriver::isSwitching10() {
    if (time_switched == 0) {
        time_switched = millis();
    }
    if (millis() - time_switched < 1000) { 
        switched_count++;
    } else {
        time_switched = 0;
    }
    if (switched_count > 9) {
        return true;
    } else {
        return false;
    }
}