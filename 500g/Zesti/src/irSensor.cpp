#include "irSensor.h"

irSensor::irSensor() : irDetected(false) {
}

bool irSensor::getirSensor() {
    return irDetected;
}

void irSensor::setirSensor(bool value) {
    irDetected = value;
}
