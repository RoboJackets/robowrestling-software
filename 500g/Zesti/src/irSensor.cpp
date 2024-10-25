#include "include/IRSensor.h"

IRSensor::IRSensor() : irDetected(false) {
}

int IRSensor::getIRSensor() {
    return irDetected;
}

void IRSensor::setIRSensor(int value) {
    irDetected = value;
}
