#include "sensors/IRSensor.h"

IRSensor::IRSensor() {
    value = 0;
    sum = 0;
}

IRSensor::IRSensor(int sensorValue) {
    value = sensorValue;
}

int IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(int sensorValue) {
    if (sensorValue && sum < 10) {
        sum++;
    }
    else if (!sensorValue && sum > 0) {
        sum--;
    }
    value = (sum > 5) ? 1 : 0;;
}

void IRSensor::setValue(int sensorValue, int concurrency) {
    if (sensorValue && sum < concurrency) {
        sum++;
    }
    else if (!sensorValue && sum > 0) {
        sum--;
    }
    value = (sum > (concurrency / 2)) ? 1 : 0;;
}

/**
 * debug function
 */
int IRSensor::getSum() {
    return sum;
}