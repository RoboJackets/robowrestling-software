#include "Robot/robotState.hpp"
#include <Arduino.h>
#ifndef TEMPORARII_HPP

#define TEMPORARII_HPP 

class Temporarii : public RobotState {
    private: 
        MotorDriver frontLeftMotorPin;
        MotorDriver frontRightMotorPin;
        MotorDriver backLeftMotorPin;
        MotorDriver backRightMotorPin;
        LineSensor topLeftLinePin;
        LineSensor topRightLinePin;
        LineSensor backLeftLinePin;
        LineSensor backRightLinePin;
        IrSensor midIrPin;
        IrSensor midLeftIrPin;
        IrSensor midRightIrPin;
        IrSensor leftIrPin;
        IrSensor rightIrPin;
    public:
        Temporarii();
};

#endif