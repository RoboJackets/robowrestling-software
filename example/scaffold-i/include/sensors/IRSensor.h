#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
private:
    /**represensents sensor value*/
    bool value;
public:
    IRSensor();
    IRSensor(bool sensorValue);
    bool getValue();
    void setValue(bool sensorValue);
};

#endif