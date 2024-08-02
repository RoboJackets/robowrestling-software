#include <Arduino.h>
#include <cstdint>


#pragma once


class StartModule {
    private:
        u_int8_t _signalPin;

    public: 
        StartModule(u_int8_t signalPin);

        bool isActive();

};
