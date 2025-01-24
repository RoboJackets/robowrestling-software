#ifndef IRSENSOR_H
#define IRSENSOR_H


class IRSENSOR{
private:
    int pin;
    bool value;

public: 
    
    IRSENSOR(int pin);
    bool getValue();

};

#endif