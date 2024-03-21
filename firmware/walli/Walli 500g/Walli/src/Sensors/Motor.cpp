#include <Arduino.h>
#include <SoftwareSerial.h>

class Motor {
    private:
        int _pin;
        int _speed;
    public:
        Motor(int pin, int speed) {
            _pin = pin;
            pinMode(_pin, OUTPUT);
            _speed = speed;
        }

        void forwards() {
            digitalWrite(_pin, _speed);
        }

        void backwards() {
            digitalWrite(_pin, -_speed);
        }

        void off() {
            digitalWrite(_pin, 0);
        }

};