#include "../../include/common.h"

MotorDriver::MotorDriver() {}

MotorDriver::MotorDriver(uint8_t fwdPin, uint8_t revPin) {
    this->fwdPin = fwdPin;
    this->revPin = revPin;
}

void MotorDriver::moveMotor(int powerFwd, int powerRev) {
    analogWrite(this->fwdPin, powerFwd);
    analogWrite(this->revPin, powerRev);
}
