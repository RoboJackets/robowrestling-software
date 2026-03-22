#ifndef DOUBLELINESENSOR_HPP_
#define DOUBLELINESENSOR_HPP_

#include <Arduino.h>
#include <cmath>

#define ANALOG_CALIBRATE_RUNS 25
#define LINE_THRESHOLD 300

class DoubleLineSensor {
    private:
        int pin_number;
        int floor_value;

    public:
        DoubleLineSensor(int pin_number);
        bool is_sensing();
        void calibrate();
};

#endif // DOUBLELINESENSOR_HPP_
