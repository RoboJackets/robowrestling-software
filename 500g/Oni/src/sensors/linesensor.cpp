#include "../../include/sensors/linesensor.h"
#include <Arduino.h>

class LINESENSOR{
private:
    int pin;
    int value;

public: 
    int getValue() {
        int value = digitalRead(pin);
        return value;
    }

};