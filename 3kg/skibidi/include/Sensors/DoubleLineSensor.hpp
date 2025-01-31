#ifndef DOUBLELINESENSOR_HPP_
#define DOUBLELINESENSOR_HPP_

#include <Arduino.h>
#include <cmath>

#define ANALOG_CALIBRATE_RUNS 25
#define LINE_THRESHOLD 300

class DoubleLineSensor {
    private:
        int nor_pin_number;
        int analog_pin_number_1;
        int analog_pin_number_2;
        int floor_value;
        bool analog_mode;

    public:
        DoubleLineSensor(int pin_number);
        DoubleLineSensor(int analog_pin_number_1, int analog_pin_number_2);
        bool is_sensing();
        void calibrate_analog();
};

#endif // DOUBLELINESENSOR_HPP_
