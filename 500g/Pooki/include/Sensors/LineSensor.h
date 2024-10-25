#include "../common.h"

class LineSensor {
    private:
        uint8_t pin;
    public: 
        LineSensor(uint8_t pin);
        int getValue();
};