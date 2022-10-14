#ifndef SENSOR_H 
#define SENSOR_H
#include <Arduino.h>


class Sensor {
private: 
    int _receivePin; 
    int _transmitPin; 

public: 
    Sensor() {}
    Sensor(int receivePin, int transmitPin) : _receivePin(receivePin),
         _transmitPin(transmitPin) {}
     ~Sensor() {}
    virtual bool Poll() = 0;
    virtual byte* GetBytes() = 0;

}; 


#endif 