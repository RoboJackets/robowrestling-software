#include "../../include/common.h"

DipSwitch::DipSwitch() {}

DipSwitch::DipSwitch(uint8_t pin1, uint8_t pin2) {
    this->pin1 = pin1;
    this->pin2 = pin2;
}

int DipSwitch::getValueSwitch1() {
    return analogRead(this->pin1);
}

int DipSwitch::getValueSwitch2() {
    return analogRead(this->pin2);
}

uint8_t DipSwitch::getStrat() {
    uint16_t threshold = 500;
    bool switch1_status = analogRead(this->pin1) > threshold ? true : false;
    bool switch2_status = analogRead(this->pin2) > threshold ? true : false;

    if (!switch1_status && !switch2_status) {
        // 0 0 -> strat one
        return 1;
    } else if (switch1_status && !switch2_status) {
        // 1 0 -> strat two
        return 2;
    } else if (!switch1_status && switch2_status) {
        // 0 1 -> strat three
        return 3;
    } else if (switch1_status && switch2_status) {
        // 1 1 -> strat four
        return 4;
    } else {
        return 0;
    }

}