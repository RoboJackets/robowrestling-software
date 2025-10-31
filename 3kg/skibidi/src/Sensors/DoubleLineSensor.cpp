#include "Sensors/DoubleLineSensor.hpp"

DoubleLineSensor::DoubleLineSensor(int pin_number) {
    this->pin_number = pin_number;
    pinMode(this->pin_number, INPUT);
}

bool DoubleLineSensor::is_sensing() {
    return abs(analogRead(this->pin_number) - this->floor_value) > LINE_THRESHOLD;
}

void DoubleLineSensor::calibrate() {
    int average_reading = 0;
    for (int i = 0; i < ANALOG_CALIBRATE_RUNS; i++) {
        average_reading += analogRead(this->pin_number);
    }

    this->floor_value = average_reading / ANALOG_CALIBRATE_RUNS;
}
