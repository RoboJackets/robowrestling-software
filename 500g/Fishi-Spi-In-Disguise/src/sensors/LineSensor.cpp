#include "sensors/LineSensor.h"

LineSensor::LineSensor() {
    value = 0;
    concurrentReadings = 0;
    threshold = 500;
    calibrationCount = 0;
    calibrationCount = 0; 
}

LineSensor::LineSensor(int sensorValue) {
    value = sensorValue;
    concurrentReadings = 0;
    threshold = 500;
    calibrationCount = 0;
    calibrationCount = 0;
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

void LineSensor::calibrate(int sensorValue) {
    if (calibrationCount < 10000) {
        calibrationCount++;
        calibrationSum += sensorValue;
        threshold = (calibrationSum / calibrationCount) - 250; 
    }
}