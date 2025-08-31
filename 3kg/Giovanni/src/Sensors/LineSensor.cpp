# include "Sensors/LineSensor.hpp"

LineSensor::LineSensor() {
    val = 0;
}

int LineSensor::getVal() {
    return val;
}

void LineSensor::setVal(int input) {
    val = input;
}