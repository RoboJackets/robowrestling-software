#include<Sensors/Lidar.h>
Lidar::Lidar(int pin):WalliSensor(pin) {
    //idk
}

bool Lidar::detected() {
    return WalliSensor::read() == 1;
    //should this be zero? not sure
}

