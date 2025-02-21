#include <LineSensor.h>

LineSensor::LineSensor() {
    value = 0;
};

LineSensor::LineSensor(int sensorValue) {
    value = sensorValue;
}

void LineSensor::setValue(int sensorValue) {
    value = sensorValue;
}

int LineSensor::getValue() {
    return value;
}