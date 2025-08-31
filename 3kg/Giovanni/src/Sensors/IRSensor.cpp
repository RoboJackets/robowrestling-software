# include "Sensors/IRSensor.hpp"

IRSensor::IRSensor() {
    val = 0;
}

int IRSensor::getVal() {
    return val;
}

void IRSensor::setVal(int input) {
    val = input;
}