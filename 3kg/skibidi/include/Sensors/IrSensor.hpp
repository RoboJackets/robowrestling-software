#ifndef IRSENSOR_HPP_
#define IRSENSOR_HPP_

#include <Arduino.h>

class IrSensor {
    private:
        int pin_number;

    public:
        IrSensor(int pin_number);
        bool is_sensing();
};

#endif // IRSENSOR_HPP_
