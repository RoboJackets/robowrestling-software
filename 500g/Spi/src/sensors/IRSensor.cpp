#include "sensors/IRSensor.h"

IRSensor::IRSensor() {
    value = 0;
    sum = 0;
    pollTime = 0;
}

IRSensor::IRSensor(int sensorValue) {
    value = sensorValue;
    sum = 0;
    pollTime = 0;
}

int IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(int sensorValue) {
    value = (sum > 25) ? 1 : 0;
    if (sensorValue && sum < 50) {
        sum++;
    }
    else if (!sensorValue && sum > 0) {
        sum--;
    }
    value = (sum > 25) ? 1 : 0;
}

// void IRSensor::setValue(int sensorValue, int concurrency) {
//     if (sensorValue && sum < concurrency) {
//         sum++;
//     }
//     else if (!sensorValue && sum > 0) {
//         sum--;
//     }
//     value = (sum > (concurrency / 2)) ? 1 : 0;
// }

void IRSensor::setValue(int sensorValue, unsigned long time) {
    if (time > pollTime) {
        pollTime = time + 5;
        value = pendingvalue;
        pendingvalue = 1;
    }
    if (sensorValue == 0) {
        pendingvalue = 0;
    }
}

/**
 * debug function
 */
int IRSensor::getSum() {
    return sum;
}