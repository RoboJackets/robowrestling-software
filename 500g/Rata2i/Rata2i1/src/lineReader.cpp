#include <Arduino.h>

class lineReader {
    private:
        int pin;
    public:
        lineReader(int pin){
            this->pin = pin;
        };
        int read(){
            return digitalRead(this->pin);
        };
        void setPin(int pin){
            this->pin = pin;
        };
        int getPin(){
            return this->pin;
        };
};