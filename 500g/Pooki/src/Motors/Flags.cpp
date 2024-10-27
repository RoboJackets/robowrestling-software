#include "../../include/common.h"

Flags::Flags(uint8_t pin) {
    this->flag_servo.attach(pin);
}

void Flags::deploy() {
    flag_servo.write(180);
}