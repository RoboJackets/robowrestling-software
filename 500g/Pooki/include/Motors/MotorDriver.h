#pragma once
#include "../common.h"

class MotorDriver {
    private:
        uint8_t fwdPin;
        uint8_t revPin;
    public:
        MotorDriver();
        MotorDriver(uint8_t fwdPin, uint8_t revPin);
        void moveMotor(int powerFwd, int powerRev);
};