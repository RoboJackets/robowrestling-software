#include <IRSensor.h>

IRSensor::IRSensor(int sensorValue) {
    value = 0;
}

int IRSensor::getValue() {
    return value;
}

void IRSensor::setValue(int sensorValue) {
    value = sensorValue;
}