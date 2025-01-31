#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <Arduino.h>    // makes me sad but is necessary
#include "RoboClaw.h"

#define address 0x80

class MotorDriver {
    private:
        const int BAUD_RATE = 38400;     // speed of communication
        const int LIMIT = 10000;         // specified in the docs
        static MotorDriver *instance;
        HardwareSerial serial = Serial8; // pins of communication

        static RoboClaw *roboClaw;
        MotorDriver();
    public:
        static RoboClaw *getMotorDriver();
        static MotorDriver *getInstance();
        static int getAddress();
};
#endif