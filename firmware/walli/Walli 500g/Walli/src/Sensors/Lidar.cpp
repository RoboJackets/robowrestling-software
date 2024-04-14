#include<Sensors/Lidar.h>
/*This is the class that retrieves
* information from the lidars
*/

//constructor that just initializes the pin
Lidar::Lidar(int pin):WalliSensor(pin) {
    //idk
}

//returns whether or not the lidar detects something or not
bool Lidar::detected() {
    return this->read() == 1;
}

