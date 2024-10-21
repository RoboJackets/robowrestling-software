#include <Arduino.h>

#ifndef IR_SENSOR_H
#define IR_SENSOR_H

// Omron E3Z-D82 model
// PNP output, sensing distance 1 meter, pre-wired
// PNP - output pin provides a positive voltage when the sensor detects an object
// diffuse reflective sensing method (reflect ir light off object back to sensor)
// light source: IR

class IrSensor {

    private:
        uint8_t pin;
        bool value;

    public:
        IrSensor(uint8_t pin); 
        bool getValue();

};

#endif
