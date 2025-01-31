#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRsensor {
private:
    /*represensents sensor value*/
    int value;
public:
    IRsensor();
    IRsensor(int sensorValue);
    int getValue();
    void setValue(int sensorValue);
    bool isDetecting();
};

#endif