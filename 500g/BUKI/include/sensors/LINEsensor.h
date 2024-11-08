#ifndef LINESENSOR_H
#define LINESENSOR_H

class LINEsensor {
private:
    /*represensents sensor value*/
    bool value;
public:
    LINEsensor();
    LINEsensor(bool sensorValue);
    bool getValue();
    void setValue(bool sensorValue);
};

#endif