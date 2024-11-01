#pragma once
#include "../common.h"


class Flags {
    private: 
        uint8_t pin;
        bool deployed;
    public:
        Servo flag_servo;
        Flags();
        Flags(uint8_t pin);
        void deploy();
};