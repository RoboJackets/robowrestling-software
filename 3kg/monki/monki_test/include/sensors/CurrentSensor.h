#include <Arduino.h>


#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

class CurrentSensor {
    private:
        int current;
    public:
        int getCurrent();

};


#endif