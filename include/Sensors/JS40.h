#include <Arduino.h>
#include <cstdint>

#pragma once

class JS40 {
    private:
        u_int8_t _signalPin;

    public: 
        JS40();
        JS40(u_int8_t signalPin);

        bool objectDetected(); 

};

