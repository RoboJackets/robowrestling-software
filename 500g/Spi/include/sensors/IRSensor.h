#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
private:
    /*represensents sensor value*/
    int sum; // sum of past x readings
    int value;
    unsigned long pollTime;
    int pendingvalue;
public:
    IRSensor();
    IRSensor(int sensorValue);
    int getValue();
    int getSum();
    void setValue(int sensorValue);
    // void setValue(int sensorValue, int concurrency);
    void setValue(int sensorValue, unsigned long time);
};

#endif