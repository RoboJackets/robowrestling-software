#include "Sensors/IrSensor.h"

// type | Class Name | function name
bool IrSensor::getValue() {
    return value;
}

void IrSensor::setValue(bool sensorValue) {
    value = sensorValue;
}