#include "../../include/state/sensors/LineSensor.h"
#include <Arduino.h>

    LINESENSOR::LINESENSOR(int pin){
        this->pin = pin;
    }
    
    int LINESENSOR::getValue() {
        int value = analogRead(pin);
        return value;
    }
    

