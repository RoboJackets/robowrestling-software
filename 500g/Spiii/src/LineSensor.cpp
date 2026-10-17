#include "LineSensor.hpp"

LineSensor::LineSensor() {
    threshold = 512; // mid value
}

LineSensor::LineSensor(int _threshold) {
    threshold = _threshold;
}

LineSensorValue LineSensor::getValue() {
    if (rawValue > threshold) {
        return OFF_LINE;
    } else {
        return ON_LINE;
    }
}

void LineSensor::setThreshold(int _threshold) {
    threshold = _threshold;
}

void LineSensor::setValue(int _rawValue) {
    rawValue = _rawValue;
}