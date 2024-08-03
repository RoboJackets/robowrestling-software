#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
private:
    int leftIRSensor;
    int middleIRSensor;
    int rightIRSensor;
public:
    IRSensor();
    int getLeftIRSensor();
    int getMiddleIRSensor();
    int getRightIRSensor();
    void setLeftIRSensor(int sensorValue);
    void setMiddleIRSensor(int sensorValue);
    void setRightIRSensor(int sensorValue);
};

#endif