#include "Sensors/irSensor.h"

// type | Class Name | function name
IrSensor::IrSensor() {
    value = 0;
}
bool IrSensor::getValue() {
    return value;
}

void IrSensor::setValue(bool sensorValue) {
    value = sensorValue;
}