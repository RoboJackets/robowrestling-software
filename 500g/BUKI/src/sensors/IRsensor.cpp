#include "sensors/IRsensor.h"

IRsensor::IRsensor() {
    value = 0;
}

IRsensor::IRsensor(int sensorValue) {
    value = sensorValue;
}

int IRsensor::getValue() {
    return value;
}

void IRsensor::setValue(int sensorValue) {
    value = sensorValue;
}

bool isDetecting() {
    return true;
}