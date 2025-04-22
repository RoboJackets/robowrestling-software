#include "irSensor.h"
#include <util.h>

IRSensor::IRSensor() {
    value = 0;
    counter = 0;
    average = 0;
    threshold = 0.2;
    for (int i = 0; i < 10; i++) {
        readings[i] = 0;
    }
}

IRSensor::IRSensor(int sensorValue) {
    value = sensorValue;
    threshold = 0.2;
    counter = 0;
    average = 0;
    for (int i = 0; i < 10; i++) {
        readings[i] = 0;
    }
}

IRSensor::IRSensor(int sensorValue, int threshold) {
    value = sensorValue;
    this->threshold = threshold;
    counter = 0;
    average = 0;
    for (int i = 0; i < 10; i++) {
        readings[i] = 0;
    }
}

int IRSensor::getValue() {
    if (average > threshold) {
        return 1;
    } else {
        return 0;
    }
}

double IRSensor::getAverage() {
    return average;
}

void IRSensor::setValue(int reading) {
    readings[counter] = reading;
    counter = (counter + 1) % 10;
    average = util::average(readings, 10);
}