#ifndef SERIALSENSOR_H
#define SERIALSENSOR_H
#include "Sensor.h"

class SerialSensor : public Sensor {
public: 
    SerialSensor(HardwareSerial* serial, int numBytes) 
        : Sensor(0, 0), _numBytes(numBytes) {
        
        _serial = serial; 
        _bytes = (byte*)calloc(sizeof(byte), numBytes); 
    }

    ~SerialSensor() {
        delete[] _bytes; 
    }

    bool Poll() override {
        if (_serial -> available() > 0) {
            _serial -> readBytes(_bytes, _numBytes);
        }

        return true; 
    }

    byte* GetBytes() override {
        return _bytes;
    }
protected: 
    byte* _bytes; 
    int _numBytes; 
    HardwareSerial* _serial; 
    

    


}; 

#endif 


