#include "MotorDriver.h"

MotorDriver::MotorDriver(){
    input = 0;
    speed = 0;
}

MotorDriver::MotorDriver(int inputValue, int speedValue) {
    input = inputValue;
    speed = speedValue;
}

int MotorDriver::getInput() {
    return input;
}

void MotorDriver::setInput(int inputValue) {
    input = inputValue;
}
int MotorDriver::getSpeed() {
    return speed;
}

void MotorDriver::setSpeed(int speedValue) {
    speed = speedValue;
}
