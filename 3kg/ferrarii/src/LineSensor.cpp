#include "LineSensor.hpp"

LineSensor::LineSensor(int _threshold) {
    threshold = _threshold;
}

LineSensorValue LineSensor::getValue() {
    if (rawValue1 > threshold || rawValue2 > threshold) {
        return OFF_LINE;
    } else {
        return ON_LINE;
    }
}

void LineSensor::setValue(int _rawValue1, int _rawValue2) {
    rawValue1 = _rawValue1;
    rawValue2 = _rawValue2;
}