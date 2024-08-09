#include "sensors/LineSensor.h"

LineSensor::LineSensor() {
    threshold = 500;
    value = false;
}

LineSensor::LineSensor(int thresholdValue) {
    threshold = thresholdValue;
}

LineSensor::LineSensor(bool sensorValue, int thresholdValue) {
    value = sensorValue;
    threshold = thresholdValue;
}

bool LineSensor::getValue() {
    return value;
}

void LineSensor::setValue(int sensorValue) {
    value = (sensorValue < threshold) ? false : true;
}