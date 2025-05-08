#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
private:
    /*represensents sensor value*/
    int concurrentReadings;
    int value;
public:
    IRSensor();
    IRSensor(int sensorValue);
    int getValue();
    void setValue(int sensorValue);
};

#endif