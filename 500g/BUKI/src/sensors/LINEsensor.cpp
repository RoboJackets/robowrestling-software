#include "sensors/LINEsensor.h"

LINEsensor::LINEsensor() {
    value = 0;
}

LINEsensor::LINEsensor(bool sensorValue) {
    value = sensorValue;
}

bool LINEsensor::getValue() {
    return value;
}

void LINEsensor::setValue(bool sensorValue) {
    value = sensorValue;
}