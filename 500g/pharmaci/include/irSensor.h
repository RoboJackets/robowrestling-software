#ifndef IRSENSOR_H
#define IRSENSOR_H
class irSensor {
    private: 
        bool irDetected;
    public: 
        irSensor();
        bool getirSensor();
        void setirSensor(bool value);
};
#endif
