#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
private:
    int leftLineSensor;
    int rightLineSensor;
    int backLineSensor;  
public:
    LineSensor();
    int getLeftLineSensor();
    int getRightLineSensor();
    int getBackLineSensor();
    void setLeftLineSensor(int sensorValue);
    void setRightLineSensor(int sensorValue);
    void setBackLineSensor(int sensorsValue);
};

#endif