#ifndef LINESENSOR_H
#define LINESENSOR_H

enum LineSensorValue{OFF_LINE, ON_LINE};

class LineSensor {
    private:
        int rawValue1;
        int rawValue2;
        int threshold1;
        int threshold2;
        int value;
    public:
        LineSensor();
        LineSensor(int _threshold1, int _threshold2);
        LineSensorValue getValue();
        void setThreshold(int _threshold1, int _threshold2);
        void setValue(int _rawValue1, int _rawValue2);
};

#endif