#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "utility/AutoTimer.hpp"

class MotorDriver {
private:
    int speed;
    int direction;
    bool isBraking;
    AutoTimer *speedChangeTimer;
public:
    MotorDriver();
    void setSpeed(int speedValue);
    void setDirection(int directionValue);
    bool getIsBraking();
    void setIsBraking(bool _isBraking);
    int getIn1();
    int getIn2();
};

#endif