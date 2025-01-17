#include "IRSensor.h"
#include <util.h>

IRSensor::IRSensor() {
    value = 0;
}

IRSensor::IRSensor(int sensorValue) {
    value = sensorValue;
}

int IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(int reading) {
    readings[counter] = reading;
    counter = (counter + 1) % 10;
    value = util::average(readings, 10);
}