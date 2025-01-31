#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
private:
    int value;
    int readings[10];
    int threshold;
    int counter;
public:
    IRSensor();
    IRSensor(int sensorValue);
    int getValue();
    void setValue(int sensorValue);
};

#endif