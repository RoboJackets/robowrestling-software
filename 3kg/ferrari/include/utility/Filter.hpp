#ifndef FILTER_H
#define FILTER_H

#include <queue> 
using namespace std;

class Filter {
private:
    // Represents the last 10 readings from the sensor.
    std::queue<int> *values;
    // Represents whether we are filtering a analog or digial sensor
    bool isDigital;
    int rollingSum;
public:

    /**
     * constructor
     * @param sensorType set true if sensor is digital, set false if sensor is analog.
     */
    Filter(bool sensorType);

    /**
     * rawSensorValue should be a 1 or a 0! 
     */
    void filterSensor(int rawSensorValue);
    int getSensorValue();
};

#endif