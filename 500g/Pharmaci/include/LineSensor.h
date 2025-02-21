#ifndef LINESENSOR_H
#define LINESENSOR_H

class LineSensor {
    private:
        int value;

    public:
        LineSensor();
        LineSensor(int sensorValue);
        void setValue(int sensorValue);
        int getValue();
};

#endif