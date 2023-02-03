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
    TFMini(Stream* stream) {
        tfm.begin(stream); 
    }

    bool Poll() override {
        tfm.getData(_dist); 
        return true; 
    }

    int GetDistance() override {
        return _dist; 
    }

    ~TFMini() {}
};


#endif 