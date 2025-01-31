#include "../../include/state/sensors/irsensor.h"
#include "Arduino.h"


    IRSENSOR::IRSENSOR(int pin){
        this->pin = pin;
    }
    
    bool IRSENSOR::getValue() {
        bool value = digitalRead(pin);
        return value;
    }
