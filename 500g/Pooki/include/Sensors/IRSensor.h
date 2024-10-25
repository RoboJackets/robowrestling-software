#pragma once
#include "../common.h"

class IRSensor {
    private:
        uint8_t pin;
    public:
        IRSensor(uint8_t pin);
        bool getValue();
};