#include <Arduino.h>

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

class MotorDriver {
    private:
        uint8_t pins[2];
        uint8_t speed;
        bool direction;

    public:
        void setSpeed(uint8_t speed);
        void setDirection(bool direction);

        uint8_t getSpeed();
        bool getDirection();

};

#endif