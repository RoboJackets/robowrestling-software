#ifndef LIDAR
#define LIDAR
#include<Sensors/WalliSensor.h>

class Lidar : public WalliSensor {
    private:
        
    public:
        Lidar(int pin);


        bool detected();

        void writeDetected(bool v);
};
#endif