#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
private:
    /*represensents sensor value*/
    int value;
public:
    LineSensor();
    LineSensor(int sensorValue);
    int getValue();
    void setValue(int sensorValue);
};

#endif