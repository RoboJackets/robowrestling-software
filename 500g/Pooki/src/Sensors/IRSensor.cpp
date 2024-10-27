#include "../../include/common.h"

IRSensor::IRSensor(uint8_t pin) {
    this->pin = pin;
}

bool IRSensor::getValue() {
    return digitalRead(this->pin);
}
 