#include "Sensors/IRSensor.h"

IRSensor::IRSensor() {
    leftIRSensor = 0;
    middleIRSensor = 0;
    rightIRSensor = 0;
}

int IRSensor::getLeftIRSensor() {
    return leftIRSensor;
}

int IRSensor::getMiddleIRSensor() {
    return middleIRSensor;
}

int IRSensor::getRightIRSensor() {
    return rightIRSensor;
}

void IRSensor::setLeftIRSensor(int sensorValue) {
    leftIRSensor = sensorValue;
}

void IRSensor::setMiddleIRSensor(int sensorValue) {
    middleIRSensor = sensorValue;
}

void IRSensor::setRightIRSensor(int sensorValue) {
    rightIRSensor = sensorValue;
}