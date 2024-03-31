#include <Sensors/WalliSensor.h>


        WalliSensor::WalliSensor(int pin) {
            _pin = pin;
        }

        int WalliSensor::read() {
            //overwritten in child classes
            return digitalRead(_pin);
        }
