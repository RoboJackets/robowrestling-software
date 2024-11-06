#include "sensors/IRSensor.h"

IRSensor::IRSensor() {
    value = 0;
}

IRSensor::IRSensor(int sensorValue) {
    value = sensorValue;
}

int IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(int sensorValue) {
    if (sensorValue) {
        concurrentReadings++;
    } else {
        concurrentReadings = 0;
    }
    if (concurrentReadings > 10) {
        value = 1;
    } else {
        value = 0;
    }
}