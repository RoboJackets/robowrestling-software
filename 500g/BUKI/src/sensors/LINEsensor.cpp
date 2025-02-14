#include "sensors/LINEsensor.h"

LINEsensor::LINEsensor() {      // constructor
    value = 0;
}

LINEsensor::LINEsensor(int sensorValue) {      // constructor
    value = sensorValue;
}

int LINEsensor::getValue() {          // gets line sensor value (function)
    return value;
}

void LINEsensor::setValue(int sensorValue) {       // sets line sensor value (function)
    value = sensorValue;
}