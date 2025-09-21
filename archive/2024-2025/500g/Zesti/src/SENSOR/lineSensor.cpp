#include "Zesti/include/SENSOR/LineSensor.h"

int LineSensor::getValue() {
    return value;
}

void LineSensor::setValue(int newValue) {
    value = newValue;
}
