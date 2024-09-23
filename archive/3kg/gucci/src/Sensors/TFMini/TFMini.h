#ifndef TFMINI_H
#define TFMINI_H
#include <Sensors/DistanceSensor.h>
#include <Sensors/Sensor.h>
#include <SoftwareSerial.h>

#include <memory>
#include <TFMPlus.h>
//#include "../lib/TFMPlus/src/TFMPlus.h"

constexpr uint64_t WAIT_MS = 50; 


class TFMini : public Sensor, DistanceSensor<int> {
private:
    std::unique_ptr<SoftwareSerial> _serial;
    TFMPlus tfm;

    int16_t _dist;
    uint32_t _lastRead; 


public:
    TFMini(Stream* stream) {
        tfm.begin(stream);
        _lastRead = millis(); 
    }

    TFMini(int rx, int tx) {
        _serial = std::make_unique<SoftwareSerial>(rx, tx);
        _serial -> begin(115200);
        tfm.begin(_serial.get());
        _lastRead = millis();
    }

    bool Poll() override {
        bool res = false; 
        //Serial.println("polled");
        res = tfm.getData(_dist);
        _lastRead = millis(); 
        return res;
    }

    int GetDistance() override {
        return _dist;
    }

    ~TFMini() {}
};


#endif
