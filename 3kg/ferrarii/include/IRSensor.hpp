#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
    private:
        int value;
    public:
        int getValue();
        void setValue(int _value);
};

#endif