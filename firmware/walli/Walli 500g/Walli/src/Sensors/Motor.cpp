#include <Sensors/Motor.h>

Motor::Motor(int forward_pin, int backward_pin) {
    _forward_pin = forward_pin;
    _backward_pin = backward_pin;
    pinMode(_forward_pin, OUTPUT);
    pinMode(_backward_pin, OUTPUT);
}

void Motor::forwards() {
    digitalWrite(_forward_pin, 1);
    digitalWrite(_backward_pin, 0);
}

void Motor::backwards() {
    digitalWrite(_forward_pin, 0);
    digitalWrite(_backward_pin, 1);
}

void Motor::off() {
    digitalWrite(_forward_pin, 1);
    digitalWrite(_backward_pin, 1);
}
