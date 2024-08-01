#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <Arduino.h>
#include "Sensor.h"

class LineSensor : public Sensor {
public:
    LineSensor(int pin) : _pin(pin) {
     pinMode(pin, INPUT);
    }
    ~LineSensor() {}

    int read() { return analogRead(_pin); }

   bool Poll() override {
        _detected = analogRead(_pin);
        return true;
   }

   int GetDetection() {
        return _detected;
   }

private:
    int _pin;
    int _detected = 0;
};

#endif
