#include <Arduino.h>

class irSensor {
    private:
        int pin;
    public:
        irSensor(int pin){
            this->pin = pin;
        };
        int read(){
            return digitalRead(this->pin);
        };
        void setPin(int pin);
        int getPin();
};