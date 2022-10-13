#include <Arduino.h>
#include <stdexcept>
#include "motor_controller/controller.h"

void move(double voltage, bool individual = false) {
    int mapped_voltage = map(voltage, 0, 5, -32768, 32767);
    analogWrite(PIN_S1, mapped_voltage);
}

void turn(double voltage, bool individual = false) {
    int mapped_voltage = map(voltage, 0, 5, -32768, 32767);
    analogWrite(PIN_S2, mapped_voltage);
}

void stop() {
    analogWrite(PIN_S1, 0);
    analogWrite(PIN_S2, 0);
}
