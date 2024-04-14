#ifndef WALLISENSOR
#define WALLISENSOR
#include <Arduino.h>


class WalliSensor {
    private:
        //the pin that the sensor is attached to
        int _pin;
    public:
        //constructor
        WalliSensor(int pin);

        //get the value of the sensor
        int read();
};
#endif