#ifndef IRSENSOR_H
#define IRSENSOR_H

class IRSensor {
    private: 
        bool value;
    public: 
        bool getValue();
        void setValue(bool newValue);  
};

#endif
