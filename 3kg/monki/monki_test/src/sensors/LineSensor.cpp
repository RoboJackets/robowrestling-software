#include "../../include/common.h"

LineSensor::LineSensor(uint8_t pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}

int LineSensor::getValue() {
    return analogRead(pin);
}