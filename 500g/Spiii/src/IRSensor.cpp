#include "IRSensor.hpp"
    
int IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(int _value) {
    value = _value;
}