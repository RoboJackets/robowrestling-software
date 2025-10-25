#include "MotorDriver.h"

MotorDriver::MotorDriver() {
    speed = 0;
    direction = 0;
    speedChangeTimer = new AutoTimer(1);
}

void MotorDriver::setDirection(int directionValue) {
    direction = directionValue;
}

/**
 * sets speed with acceleration implementation
 */
void MotorDriver::setSpeed(int speedValue) {
    if (speedValue < speed) {
        speed = speedValue;
    }
    if (speedValue > speed && speedChangeTimer->getReady()) {
        speedChangeTimer->resetTimer();
        speed++;
    }
}

int MotorDriver::getIn1() {
    if (isBraking) {
        return 255;
    }
    return direction == 1 ? speed : 0;
}

int MotorDriver::getIn2() {
    if (isBraking) {
        return 255;
    }
    return direction == 1 ? 0 : speed;
}

bool MotorDriver::getIsBraking() {
    return isBraking;
}

void MotorDriver::setIsBraking(bool _isBraking) {
    isBraking = _isBraking;
}