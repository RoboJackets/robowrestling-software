#include "include/LineSensor.h"

LineSensor::LineSensor() : lineDetected(false) {
}

bool LineSensor::getLineSensor() {
    return lineDetected;
}

void LineSensor::setLineSensor(bool value) {
    lineDetected = value;
}
