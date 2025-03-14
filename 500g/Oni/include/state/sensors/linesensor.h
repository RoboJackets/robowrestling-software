#ifndef LINESENSOR_H
#define LINESENSOR_H


class LINESENSOR{
private:
    int pin;
    int value;

public: 
    LINESENSOR(int pin);
    void setValue(int new_val);
    int getValue();

};

#endif