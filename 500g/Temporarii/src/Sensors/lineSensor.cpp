#include "Sensors/lineSensor.h"

LineSensor::LineSensor() {
    value = 0;
}
int LineSensor::getValue() {
    return value;
}

void LineSensor::setValue(int sensorValue) {
    value = sensorValue;
}
