#include <Arduino.h>

#ifndef IR_SENSOR_H
#define IR_SENSOR_H

class IrSensor {

    private:
        uint8_t pin;
        bool value;

    public:
        IrSensor(uint8_t pin); 
        bool getValue();

};

#endif
