#ifndef IRSENSOR_H
#define IRSENSOR_H

class IrSensor{
    private:
        bool value;
    public:
        bool getValue();
        void setValue(bool input);
};

#endif