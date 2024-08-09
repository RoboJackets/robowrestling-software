#include "sensors/IRSensor.h"

IRSensor::IRSensor() {
    value = false;
}

IRSensor::IRSensor(bool sensorValue) {
    value = sensorValue;
}

bool IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(bool sensorValue) {
    value = sensorValue;
}