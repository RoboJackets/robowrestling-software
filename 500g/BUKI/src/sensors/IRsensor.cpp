#include "sensors/IRsensor.h"

IRsensor::IRsensor() {      // constructor
    value = 0;
}

IRsensor::IRsensor(int sensorValue) {       // constructor
    value = sensorValue;
}

int IRsensor::getValue() {      // gets IR sensor value (function)
    return value;
}

void IRsensor::setValue(int sensorValue) {      // sets IR sensor value (function)
    value = sensorValue;
}

bool isDetecting() {        // returns true if IR sensor is functioning (function)
    return true;
}