#include <Arduino.h>
#include <SoftwareSerial.h>

class Motor {
    private:
        int _forward_pin;
        int _backward_pin;
    public:
        Motor(int forward_pin, int backward_pin) {
            _forward_pin = forward_pin;
            _backward_pin = backward_pin;
            pinMode(_forward_pin, OUTPUT);
            pinMode(_backward_pin, OUTPUT);
        }

        void forwards() {
            digitalWrite(_forward_pin, 1);
            digitalWrite(_backward_pin, 0);
        }

        void backwards() {
            digitalWrite(_forward_pin, 0);
            digitalWrite(_backward_pin, 1);
        }

        void off() {
            digitalWrite(_forward_pin, 1);
            digitalWrite(_backward_pin, 1);
        }

};