#include <LineSensor.h>

LineSensor::LineSensor(int sensorValue) {
    value = 0;
}

int LineSensor::getValue() {
    return value;
}

void LineSensor::setValue(int sensorValue) {
    value = sensorValue;
}