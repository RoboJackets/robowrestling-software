#ifndef LINESENSOR_H
#define LINESENSOR_H

enum LineSensorValue{OFF_LINE, ON_LINE};

class LineSensor {
    private:
        int rawValue;
        int threshold;
        int value;
    public:
        LineSensor();
        LineSensor(int _threshold);
        LineSensorValue getValue();
        void setThreshold(int threshold);
        void setValue(int _rawValue);
};

#endif