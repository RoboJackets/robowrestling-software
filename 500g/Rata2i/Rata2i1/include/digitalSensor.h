#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

class digitalSensor {
    private:
        int pin;
    public:
        digitalSensor(int pin);
        int read();
        void setPin(int pin);
        int getPin();
};

#endif