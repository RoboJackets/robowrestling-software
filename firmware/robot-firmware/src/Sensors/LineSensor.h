#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <Arduino.h>

class LineSensor {
public:
    LineSensor(int pin) : _pin(pin) {}
    ~LineSensor() {}

    int read() { return analogRead(_pin); }

private:
    int _pin;
};

#endif