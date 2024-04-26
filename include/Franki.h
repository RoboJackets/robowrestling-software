#include <Arduino.h>
#include "Sensors/LineSensor.h"

#pragma once

class Franki {
    private: 
        bool atBounds;
        LineSensor _lineSensorLeft;
        LineSensor _lineSensorRight;


    
    public: 
        void sampleFloor();

        void printValuesAnalog(u_int8_t pin);
        void printValuesDigital(u_int8_t pin);
};

