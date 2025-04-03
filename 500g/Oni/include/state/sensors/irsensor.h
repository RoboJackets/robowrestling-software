#ifndef IRSENSOR_H
#define IRSENSOR_H


class IRSENSOR{
private:
    int pin;
    int value;

public: 
    
    IRSENSOR(int pin);
    int getValue();
    void setValue(int new_val);

};

#endif