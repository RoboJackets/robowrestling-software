#include <Arduino.h>
#include "../include/Sensors/JS40.h"



JS40::JS40(u_int8_t signalPin) : _signalPin(signalPin) {
    pinMode(_signalPin, INPUT);
}

bool JS40::objectDetected() {
    return digitalRead(_signalPin) == HIGH;
}
