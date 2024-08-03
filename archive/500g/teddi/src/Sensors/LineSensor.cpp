#include "Sensors/LineSensor.h"

LineSensor::LineSensor() {
    leftLineSensor = 0;
    rightLineSensor = 0;
    backLineSensor = 0;
}

int LineSensor::getLeftLineSensor() {
    return leftLineSensor;
}

int LineSensor::getRightLineSensor() {
    return rightLineSensor;
}

int LineSensor::getBackLineSensor() {
    return backLineSensor;
}

void LineSensor::setLeftLineSensor(int sensorValue) {
    leftLineSensor = sensorValue;
}

void LineSensor::setRightLineSensor(int sensorValue) {
    rightLineSensor = sensorValue;
}

void LineSensor::setBackLineSensor(int sensorValue) {
    backLineSensor = sensorValue;
}