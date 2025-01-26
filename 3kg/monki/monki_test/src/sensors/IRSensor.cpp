#include "../../include/common.h"

IrSensor::IrSensor(uint8_t pin) {
    this->pin = pin;
} 

bool IrSensor::getValue() {
    return digitalRead(pin);
}