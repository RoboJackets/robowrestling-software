#include "lineSensor.h"

lineSensor::lineSensor() : lineDetected(false) {
}

bool lineSensor::getLineSensor() {
    return lineDetected;
}

void lineSensor::setLineSensor(bool value) {
    lineDetected = value;
}
