#include "Sensors/DoubleLineSensor.hpp"

DoubleLineSensor::DoubleLineSensor(int pin_number) {
    this->nor_pin_number = pin_number;
    this->analog_mode = false;

    pinMode(this->nor_pin_number, INPUT);
}

DoubleLineSensor::DoubleLineSensor(int analog_pin_number_1, int analog_pin_number_2) {
    this->analog_pin_number_1 = analog_pin_number_1;
    this->analog_pin_number_2 = analog_pin_number_2;
    this->analog_mode = true;

    pinMode(this->analog_pin_number_1, INPUT);
    pinMode(this->analog_pin_number_2, INPUT);
}

bool DoubleLineSensor::is_sensing() {
    if (this->analog_mode) {
        return abs(analogRead(this->analog_pin_number_1) - this->floor_value) > LINE_THRESHOLD
            && abs(analogRead(this->analog_pin_number_2) - this->floor_value) > LINE_THRESHOLD;
    } else {
        return digitalRead(this->nor_pin_number) == 1;
    }
}

void DoubleLineSensor::calibrate_analog() {
    int average_reading = 0;
    for (int i = 0; i < ANALOG_CALIBRATE_RUNS; i++) {
        average_reading += (analogRead(this->analog_pin_number_1) + analogRead(this->analog_pin_number_2)) / 2;
    }

    this->floor_value = average_reading / ANALOG_CALIBRATE_RUNS;
}
