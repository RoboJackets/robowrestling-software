#include "sensors/LINEsensor.h"

LINEsensor::LINEsensor() {      // constructor
    value = 0;
}

LINEsensor::LINEsensor(bool sensorValue) {      // constructor
    value = sensorValue;
}

bool LINEsensor::getValue() {          // gets line sensor value (function)
    return value;
}

void LINEsensor::setValue(bool sensorValue) {       // sets line sensor value (function)
    value = sensorValue;
}