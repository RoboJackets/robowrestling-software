#include "sensors/IRSensor.h"
#include <Arduino.h>

IrSensor::IrSensor(uint8_t pin) {
    this->pin = pin;
} 

bool IrSensor::getValue() {
    return digitalRead(pin);
}