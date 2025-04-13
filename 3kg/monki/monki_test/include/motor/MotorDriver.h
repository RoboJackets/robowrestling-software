#include <Arduino.h>
//why is this giving me an error lmao

#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

class MotorDriver {
    private:
        uint8_t *pwm_pin;
        uint8_t *dir_pin;
        uint8_t speed;
        bool direction;

    public:
        void setSpeed(uint8_t speed);
        void setDirection(bool direction);
//to test motor drivers, hook up to the motor drivers and monitoring the voltages , tells you if motor is doing what you think it is - 12 volt robot converts power supply to 128 - 6 volts
        uint8_t getSpeed();
        //include some sort of failsafe 
        bool getDirection();

};

#endif