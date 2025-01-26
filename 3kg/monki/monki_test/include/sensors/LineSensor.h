#include <Arduino.h>

#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

class LineSensor {
    private:
        uint8_t pin;
        int value;

    public:
        LineSensor(uint8_t pin);
        int getValue();
        
};

#endif 