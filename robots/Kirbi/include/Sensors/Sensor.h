#ifndef SENSOR_H
#define SENSOR_H

/*
    Normally you would want to separate .h (header) and .cpp (C++) files
    because of how header files and #include works.
    Basically, it's because when you #include a file, the C/C++
    pre-processor copy-pastes the #include'd file into the current file.

    However, it's okay for these Sensor classes to be implemented entirely
    in header files. The implementations are small enough to where
    #including these files won't bloat the executable too much.
*/

class Sensor {
private:
    int _receivePin;
    int _transmitPin;

public:
    Sensor() {}
    Sensor(int receivePin, int transmitPin) : _receivePin(receivePin), _transmitPin(transmitPin) {}
    ~Sensor() {}
    virtual bool Poll() = 0;
};

#endif
