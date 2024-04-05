#include <Sensors/WalliSensor.h>

//see include\Sensors\WalliSensor.h
WalliSensor::WalliSensor(int pin) {
    _pin = pin;
}

int WalliSensor::read() {
    return digitalRead(_pin);
}
