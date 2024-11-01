#pragma once
#include "../common.h"

class StartModule {
    private:
        uint8_t pin;
        bool activated;
    public:
        StartModule();
        StartModule(uint8_t pin);
        bool getActivated();
};