#include "../../include/common.h"

StartModule::StartModule() {}

StartModule::StartModule(uint8_t pin) {
    this->pin = pin;
}

bool StartModule::getActivated() {
    return digitalRead(pin);
}