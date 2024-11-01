#include "../../include/common.h"

LineSensor::LineSensor() {}

LineSensor::LineSensor(uint8_t pin) {
    this->pin = pin;
}

int LineSensor::getValue() {
    return analogRead(this->pin);
}
 