#include "Sensors/IrSensor.hpp"

IrSensor::IrSensor(int pin_number) {
    this->pin_number = pin_number;
    pinMode(this->pin_number, INPUT);
}

bool IrSensor::is_sensing() {
    return digitalRead(this->pin_number) == 1;
}
