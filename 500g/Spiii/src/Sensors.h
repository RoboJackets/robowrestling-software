#pragma once
#include <Arduino.h>

class Sensors {
    public:
    void setup();

    bool lLineDetected();
    bool rLineDetected();
    bool mLineDetected();
};