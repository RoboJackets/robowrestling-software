#include <Arduino.h>
#include <SoftwareSerial.h>

class Sensor {
    private:
        int _pin;
    public:
        Sensor(int pin) {
            _pin = pin;
        }

        int read() {
            //overwritten in child classes
            return digitalRead(_pin);
        }
};