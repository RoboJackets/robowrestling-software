#include <Arduino.h>
#include "../include/Sensors/LineSensor.h"


LineSensor::LineSensor() : _value(0), _signalPin(0), _threshold(0) {}

LineSensor::LineSensor(u_int8_t signalPin) : _signalPin(signalPin), _threshold(0), _value(0) {
    pinMode(_signalPin, INPUT);
}

u_int16_t LineSensor::getValue() {
    return analogRead(_signalPin);
}

bool LineSensor::lineDetected() {
    return abs(analogRead(_signalPin) - _blackReading) > _threshold;
}

void LineSensor::setThreshold(u_int16_t threshold) {
    _threshold = threshold;
}

void LineSensor::setBlackReading(u_int16_t blackReading) {
    _blackReading = blackReading;
}
