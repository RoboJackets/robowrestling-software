#ifndef TFMINI_H 
#define TFMINI_H 
#include <Sensors/DistanceSensor.h>
#include <Sensors/Sensor.h>
#include <SoftwareSerial.h>

#include <memory> 
#include <TFMPlus.h>

class TFMini : public Sensor, DistanceSensor<int> {
private: 
    std::unique_ptr<SoftwareSerial> _serial; 
    TFMPlus tfm; 

    int16_t _dist; 


public: 
    TFMini(int rx, int tx) {
        _serial = std::make_unique<SoftwareSerial>(rx, tx); 
        _serial -> begin(115200); 
        tfm.begin(_serial.get()); 
    }

    bool Poll() override {
        tfm.getData(_dist); 
        return true; 
    }

    byte* GetBytes() override {
        return 0; 
    }

    int GetDistance() override {
        return _dist; 
    }

    ~TFMini() {}
};


#endif 