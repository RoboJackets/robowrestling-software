#ifndef IRSENSOR_H
#define IRSENSOR_H

class irSensor{
    private:
        bool line;
    public:
        bool getLine();
        bool setLine(bool input);
};

#endif