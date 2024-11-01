#pragma once
#include "../common.h"

class DipSwitch {
    private:
        uint8_t pin1;
        uint8_t pin2;
    public:
        DipSwitch();
        // pin1 A6, pin2 A7
        DipSwitch(uint8_t pin1, uint8_t pin2);
        int getValueSwitch1();
        int getValueSwitch2();
        uint8_t getStrat();
};