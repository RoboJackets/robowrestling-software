#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
    private: 
        int irDetected;
    public: 
        IRSensor();
        int getIRSensor();
        void setIRSensor(int value);
};

#endif
