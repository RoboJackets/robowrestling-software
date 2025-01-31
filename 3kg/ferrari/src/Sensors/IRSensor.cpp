#include "sensors/IRSensor.h"

IRSensor::IRSensor() {
    value = 0;
    filter = new Filter(true);
}

IRSensor::IRSensor(int sensorValue) {
    value = sensorValue;
    filter = new Filter(true);
}

int IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(int sensorValue) {
    filter->filterSensor(sensorValue);
    value = filter->getSensorValue();
}