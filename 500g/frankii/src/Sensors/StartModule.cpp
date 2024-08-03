#include <Arduino.h>
#include "../include/Sensors/StartModule.h"

StartModule::StartModule(u_int8_t signalPin) : _signalPin(signalPin) {
    pinMode(_signalPin, INPUT);
}

bool StartModule::isActive() {
    return digitalRead(_signalPin) == HIGH;
}