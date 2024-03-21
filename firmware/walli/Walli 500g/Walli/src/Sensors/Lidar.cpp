#include <Sensors/Sensor.cpp>

class Lidar: public Sensor {
    private:
        
    public:
        Lidar(int pin):Sensor(pin) {
            //idk
        }

        bool detected() {
            return Sensor::read() == 1;
            //should this be zero? not sure
        }
};