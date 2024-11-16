#ifndef START_MODULE_H
#define START_MODULE_H
#include <Arduino.h>

class StartModule {
public:
    StartModule(int pin) : _pin(pin) {
        pinMode(_pin, INPUT);
    }
    ~StartModule() {}
    bool isActive() {
        return digitalRead(_pin);
    }
    
    int getVal() {
        return analogRead(_pin);
    }

private:
    int _pin;
};

#endif