#include "../../include/state/sensors/LineSensor.h"

    LINESENSOR::LINESENSOR(int pin_ini){
         pin = pin_ini;
    }
    
    int LINESENSOR::getValue() {
        return value;
    }

    void LINESENSOR::setValue(int new_val){
        value = new_val;
    }
    

