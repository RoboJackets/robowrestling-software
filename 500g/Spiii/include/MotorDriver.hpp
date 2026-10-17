#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "Timer.hpp"

class MotorDriver {
private:
    int speed;
    int direction;
    bool isBraking;
    bool reverse;
    Timer *speedChangeTimer;
    const int DURATION = 1;
public:
    MotorDriver(bool _reverse = false);
    void setSpeed(int speedValue);
    void setDirection(int directionValue);
    bool getIsBraking();
    void setIsBraking(bool _isBraking);
    int getIn1();
    int getIn2();
};

#endif