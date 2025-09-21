#include "Zesti/include/SENSOR/irSensor.h"

bool IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(bool newValue) {
    value = newValue;
}
