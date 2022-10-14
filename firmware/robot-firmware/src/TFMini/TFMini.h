#ifndef TFMINI_H
#define TFMINI_H
#include "Sensors/SerialSensor.h"
#include "Sensors/DistanceSensor.h"

class TFMini : public SerialSensor, public DistanceSensor<int> {
public: 
    TFMini(HardwareSerial* serial, int numBytes): SerialSensor(serial, numBytes) {}

    bool Poll() override {
        SerialSensor::Poll(); 

        if (_bytes[0] != 0x59) {
            return false; // malformed header
        }

        _distance = ((int)_bytes[3] << 8 | (int)_bytes[2]);

        return true; 
    }

    int GetDistance() override {
        return _distance; 
    }

};


#endif 