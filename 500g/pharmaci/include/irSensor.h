#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
    private: 
        int value;

    public: 
        IRSensor(int sensorValue);
        int getValue();
        void setValue(int sensorValue);
};

#endif