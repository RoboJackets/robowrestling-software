#include "Sensors/lineSensor.h"

int LineSensor::getValue() {
    return value;
}

void LineSensor::setValue(int sensorValue) {
    value = sensorValue;
}
