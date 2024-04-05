#ifndef WALLISENSOR
#define WALLISENSOR
#include <Arduino.h>

class WalliSensor {
    private:
        int _pin;
    public:
        WalliSensor(int pin);

        int read();
};
#endif