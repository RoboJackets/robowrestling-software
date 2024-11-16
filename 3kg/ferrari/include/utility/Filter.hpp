#ifndef FILTER_H
#define FILTER_H

#include <queue> 
using namespace std;

class Filter {
private:
    // Represents the last 10 readings from the sensor.
    std::queue<int> values;
    int rollingSum;
public:
    Filter();
    int FilterSensor(int rawSensorValue);
};

#endif