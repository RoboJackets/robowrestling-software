#include "../../include/state/sensors/irsensor.h"


    IRSENSOR::IRSENSOR(int pin_ini){
        pin = pin_ini;
    }
    
    int IRSENSOR::getValue(){
        return value;
    }

    void IRSENSOR::setValue(int new_val){
        value = new_val;
    }
