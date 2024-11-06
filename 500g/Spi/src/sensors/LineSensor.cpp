#include "sensors/LineSensor.h"

LineSensor::LineSensor() {
    value = 0;
}

LineSensor::LineSensor(int sensorValue) {
    value = sensorValue;
}

int LineSensor::getValue() {
    return value;
}

void LineSensor::setValue(int sensorValue) {
    value = (sensorValue > getThreshold()) ? concurrentReadings = 0 : concurrentReadings++;
    if (concurrentReadings > 10) {
        value = 1;
    } else {
        value = 0;
    }
}

int LineSensor::getThreshold() {
    return threshold;
}

void LineSensor::setThreshold(int sensorValue) {
    threshold = sensorValue;
}