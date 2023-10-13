#ifndef SERIALSENSOR_H
#define SERIALSENSOR_H
#include "Sensor.h"
#include <Stream.h>

class SerialSensor : public Sensor {
public: 
    SerialSensor(Stream* serial, int numBytes) 
        : Sensor(0, 0), _numBytes(numBytes) {
        
        _serial = serial; 
        _bytes = (byte*)calloc(sizeof(byte), numBytes); 
    }

    ~SerialSensor() {
        delete[] _bytes; 
    }

    bool Poll() override {
        if (_serial -> available() >= _numBytes) {
            _serial -> readBytes(_bytes, _numBytes);
        }

        return true; 
    }

    byte* GetBytes() {
        return _bytes;
    }
protected: 
    byte* _bytes; 
    int _numBytes; 
    Stream* _serial; 
    

    


}; 

#endif 


