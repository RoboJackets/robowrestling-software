#include "MotorDriver.hpp"

MotorDriver::MotorDriver(bool _reverse = false) {
    reverse = _reverse;
    speed = 0;
    direction = 0;
    speedChangeTimer = new Timer(DURATION);
}

void MotorDriver::setDirection(int directionValue) {
    direction = directionValue;
}

/**
 * sets speed with acceleration implementation
 */
void MotorDriver::setSpeed(int speedValue) {
    int safe_speed = 100;
    if (speedValue < speed) {
        speed = speedValue;
    }
    if (speedValue > speed && speedChangeTimer->isReady()) {
        if (speedValue >= safe_speed && speed < safe_speed) {
            speed = safe_speed;
        }
        speedChangeTimer->resetTimer();
        speed++;
    }
}

int MotorDriver::getIn1() {
    if (isBraking) {
        return 255;
    }
    if (!reverse) {
        return direction == 1 ? speed : 0;
    } else {
        return direction == 1 ? 0 : speed;
    }
}

int MotorDriver::getIn2() {
    if (isBraking) {
        return 255;
    }
    if (!reverse) {
        return direction == 1 ? 0 : speed;
    } else {
        return direction == 1 ? speed : 0;
    }
}

bool MotorDriver::getIsBraking() {
    return isBraking;
}

void MotorDriver::setIsBraking(bool _isBraking) {
    isBraking = _isBraking;
}