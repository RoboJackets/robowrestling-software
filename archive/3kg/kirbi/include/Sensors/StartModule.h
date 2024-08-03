#ifndef START_MODULE_H
#define START_MODULE_H

class StartModule {
public:
    StartModule(int pin) : _pin(pin) {
        pinMode(_pin, INPUT);
    }
    ~StartModule() {}

    bool isActive() { return digitalRead(_pin); }
    int getValue() { return analogRead(_pin); }

private:
    int _pin;
};

#endif
