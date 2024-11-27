#include "motor-driver/MotorDriver.hpp"

MotorDriver *MotorDriver::instance = nullptr;

MotorDriver::MotorDriver() {
    RoboClaw newRoboClaw(&serial, LIMIT); // Serial8, 10000
    roboClaw = &newRoboClaw;
    roboClaw->begin(BAUD_RATE);
}

MotorDriver *MotorDriver::getInstance() {
    if (instance == nullptr) {
        instance = new MotorDriver();
    }
    return instance;
}

/**
 * You don't need to instantiate the motordriver,
 * it will do it for you.
 */
RoboClaw *MotorDriver::getMotorDriver() {
    if (!roboClaw) {
        MotorDriver();
    }
    return roboClaw;
}

/**
 * motordriver address for communication.
 */
int MotorDriver::getAddress() {
    return address;
}
