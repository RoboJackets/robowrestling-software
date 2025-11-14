#ifndef LINESENSOR_H
#define LINESENSOR_H

class LINEsensor {
private:
    /*represensents sensor value*/
    int value;
public:
    LINEsensor();
    LINEsensor(int sensorValue);
    int getValue();
    void setValue(int sensorValue);
};

#endif