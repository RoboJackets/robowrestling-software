#include "../../Oni/include/motor/motor_driver.h"


MotorDriver::MotorDriver() {
    setDirection(0);
    setSpeed(0);
}

int MotorDriver::getDirection() {
    return direction;
}

int MotorDriver::getSpeed() {
    return speed;
}

void MotorDriver::setDirection(int value) {
    if (!(value < 0)) {
        direction = value;
    }
}

void MotorDriver::setSpeed(int value) {
    if (!(value < 0)) {
        speed = value;
    }
}