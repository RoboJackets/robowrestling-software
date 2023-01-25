#ifndef START_MODULE_H
#define START_MODULE_H

#include <Arduino.h>

class StartModule{
public:
    StartModule(int pin) : _pin(pin) {}
    ~StartModule() {}

    bool isActive() { return digitalRead(_pin); }
    int getValue() { return analogRead(_pin); }
    
private:
    int _pin;
};

#endif