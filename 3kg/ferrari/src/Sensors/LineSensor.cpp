#include "sensors/LineSensor.h"

LineSensor::LineSensor() {
    value = 0;
    filter = new Filter(false);
}

LineSensor::LineSensor(int sensorValue) {
    value = sensorValue;
    filter = new Filter(false);
}

int LineSensor::getValue() {
    return value;
}

void LineSensor::setValue(int sensorValue) {
    filter->filterSensor(sensorValue);
    value = filter->getSensorValue();
}