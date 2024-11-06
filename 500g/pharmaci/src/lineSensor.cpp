#include <LineSensor.h>

LineSensor::LineSensor(int sensorValue) {
    value = 0;
};

void LineSensor::setValue(int sensorValue) {
    value = sensorValue;
}

int LineSensor::getValue() {
    return value;
}