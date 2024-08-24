#include "sensors/LineSensor.h"

LineSensor::LineSensor() {
    threshold = 500;
    value = false;
}

LineSensor::LineSensor(bool sensorValue) {
    threshold = 500;
    value = sensorValue;
}

LineSensor::LineSensor(int thresholdValue) {
    threshold = thresholdValue;
    value = false;
}

LineSensor::LineSensor(bool sensorValue, int thresholdValue) {
    threshold = thresholdValue;
    value = sensorValue;
}

bool LineSensor::getValue() {
    return value;
}

void LineSensor::setValue(int sensorValue) {
    value = (sensorValue < threshold) ? false : true;
}