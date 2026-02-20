#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
    private: 
        int value;
    public:
        LineSensor();
        int getValue();
        void setValue(int sensorValue);
};

#endif