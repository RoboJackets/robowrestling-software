#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
private:
    /**threshold for sensor to read high or low*/
    int threshold;
    /**represensents sensor value*/
    bool value;
public:
    LineSensor();
    LineSensor(bool sensorValue);
    LineSensor(int thresholdValue);
    LineSensor(bool sensorValue, int thresholdValue);
    bool getValue();
    void setValue(int sensorValue);
};

#endif