#include <sensor.hpp>

Sensor::Sensor(){
    value = 0;
}

int Sensor::getValue() {
    return value;
}

void Sensor::setValue(int sensorValue) {
    // value = sensorValue;
    if (sensorValue == 1 && concurrency < 10) {
        concurrency++;
    } else if (sensorValue == 0) {
        concurrency = 0;
    }
    if (concurrency >= 50) {
            value = 1;
    } else {
        value = 0;
    }
    value = sensorValue;
}