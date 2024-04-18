#ifndef LINESENSOR
#define LINESENSOR
#include<Sensors/WalliSensor.h>

class LineSensor : public WalliSensor {
    private:
        int _base;
        int _threshold;
        int sample();
    public:
        LineSensor(int pin);

        bool onLine();
        void write(int n);

};
#endif