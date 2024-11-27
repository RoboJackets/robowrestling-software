#ifndef IRSENSOR_H
#define IRSENSOR_H

#include "utility/Filter.hpp"

class IRSensor {
private:
    /*represensents sensor value*/
    Filter *filter;
    int value;
public:
    IRSensor();
    IRSensor(int sensorValue);
    int getValue();
    void setValue(int sensorValue);
};

#endif