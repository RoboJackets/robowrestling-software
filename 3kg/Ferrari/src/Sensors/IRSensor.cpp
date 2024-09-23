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
    value = sensorValue;
}