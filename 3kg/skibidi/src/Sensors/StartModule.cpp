#include "Sensors/StartModule.hpp"

StartModule::StartModule(int pin_number) {
    this->pin_number = pin_number;

    pinMode(this->pin_number, INPUT);
}

bool StartModule::is_started() {
    return digitalRead(this->pin_number) == 1;
}
