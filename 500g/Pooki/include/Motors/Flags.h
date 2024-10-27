#pragma once
#include "../common.h"


class Flags {
    private: 
        uint8_t pin;
        Servo flag_servo;
        bool deployed;
    public:
        Flags(uint8_t pin);
        void deploy();
};