#include <IRSensor.h>

IRSensor::IRSensor(int sensorValue) {
    value = 0;
}

void IRSensor::setValue(int sensorValue) {
    value = sensorValue;
}

int IRSensor::getValue() {
    return value;
}

