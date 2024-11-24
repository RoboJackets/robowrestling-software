#include "Robot/Temporarii.h"
#include <Sensors/irSensor.h>

Temporarii::Temporarii() {
    // Motor Pins
    frontLeftMotorPin.setSpeed(0);
    frontRightMotorPin.setSpeed(0);
    backLeftMotorPin.setSpeed(0);
    backRightMotorPin.setSpeed(0);

    // When pin values for pins come out, replace these values
    frontLeftMotorPin.setValue(6);
    backLeftMotorPin.setValue(7);
    backRightMotorPin.setValue(10);
    frontRightMotorPin.setValue(9);

    topLeftLinePin.setValue(0);
    topRightLinePin.setValue(1);
    backLeftLinePin.setValue(2);
    backRightLinePin.setValue(3);

    midIrPin.setValue(4);
    midLeftIrPin.setValue(5);
    midRightIrPin.setValue(6);
    leftIrPin.setValue(7);
    rightIrPin.setValue(8);

    // Defines whether a pin is input or output
    // Motors
    pinMode(frontLeftMotorPin.getValue(), OUTPUT);
    pinMode(frontRightMotorPin.getValue(), OUTPUT);
    pinMode(backLeftMotorPin.getValue(), OUTPUT);
    pinMode(backRightMotorPin.getValue(), OUTPUT);

    // Line Sensors
    pinMode(topLeftLinePin.getValue(), INPUT);
    pinMode(topRightLinePin.getValue(), INPUT);
    pinMode(backLeftLinePin.getValue(), INPUT);
    pinMode(backRightLinePin.getValue(), INPUT);

    // IR Sensors
    pinMode(midIrPin.getValue(), INPUT);
    pinMode(midLeftIrPin.getValue(), INPUT);
    pinMode(midRightIrPin.getValue(), INPUT);
    pinMode(leftIrPin.getValue(), INPUT);
    pinMode(rightIrPin.getValue(), INPUT);
}