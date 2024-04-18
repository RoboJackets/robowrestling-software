#include <Sensors/WalliSensor.h>

/* Parent class for the Lidar 
*  and line sensor classes
*/

//constructor
WalliSensor::WalliSensor(int pin) {
    _pin = pin;
}

//get the value of the sensor
int WalliSensor::read() {
    return digitalRead(_pin);
}

void WalliSensor::write(bool v) {
    digitalWrite(_pin, v);
}
