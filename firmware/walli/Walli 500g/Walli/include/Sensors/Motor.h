#ifndef MOTOR
#define MOTOR
#include <Arduino.h>

class Motor {
    private:
        int _forward_pin;
        int _backward_pin;
    public:
        Motor(int forward_pin, int backward_pin);

        void forwards();

        void backwards();

        void off();

};
#endif