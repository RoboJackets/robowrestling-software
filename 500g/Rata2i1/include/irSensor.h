#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
private:
    int value;
    double average;
    int readings[10];
    int threshold;
    int counter;
public:
    IRSensor();
    IRSensor(int sensorValue);
    IRSensor(int sensorValue, int threshold);
    int getValue();
    double getAverage();
    void setValue(int sensorValue);
};

#endif