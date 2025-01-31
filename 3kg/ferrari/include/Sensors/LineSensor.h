#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "utility/Filter.hpp"

class LineSensor {
private:
    /*represensents sensor value*/
    int value;
    Filter *filter;
public:
    LineSensor();
    LineSensor(int sensorValue);
    int getValue();
    void setValue(int sensorValue);
};

#endif