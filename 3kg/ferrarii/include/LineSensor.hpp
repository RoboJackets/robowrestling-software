#ifndef LINESENSOR_H
#define LINESENSOR_H

enum LineSensorValue{OFF_LINE, ON_LINE};

class LineSensor {
    private:
        int rawValue1;
        int rawValue2;
        int value;
        int threshold;
    public:
        LineSensor(int _threshold);
        LineSensorValue getValue();
        void setValue(int _rawValue1, int _rawValue2);
};

#endif