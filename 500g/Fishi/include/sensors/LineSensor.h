#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
private:
    /*represensents sensor value*/
    int value;
    int concurrentReadings;
    int threshold;
public:
    LineSensor();
    LineSensor(int sensorValue);
    int getValue();
    void setValue(int sensorValue);
    int getThreshold();
    void setThreshold(int sensorValue);
};

#endif