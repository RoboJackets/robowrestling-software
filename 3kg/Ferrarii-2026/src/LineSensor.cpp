#include "LineSensor.hpp"

LineSensor::LineSensor() {
    threshold1 = 512; // mid value
    threshold2 = 512;
}

LineSensor::LineSensor(int _threshold1, int _threshold2) {
    threshold1 = _threshold1;
    threshold2 = _threshold2;
}

LineSensorValue LineSensor::getValue() {
    if (rawValue1 > threshold1 || rawValue2 > threshold2) {
        return OFF_LINE;
    } else {
        return ON_LINE;
    }
}

void LineSensor::setThreshold(int _threshold1, int _threshold2) {
    threshold1 = _threshold1;
    threshold2 = _threshold2;
}

void LineSensor::setValue(int _rawValue1, int _rawValue2) {
    rawValue1 = _rawValue1;
    rawValue2 = _rawValue2;
}