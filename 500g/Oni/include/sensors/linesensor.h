#ifndef LINESENSOR_H
#define LINESENSOR_H


class LINESENSOR{
private:
    int pin;
    int value;

public: 
    LINESENSOR(int pin);
    int getValue();

};

#endif