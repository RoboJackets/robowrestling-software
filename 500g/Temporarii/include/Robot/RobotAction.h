#ifndef ROBOTACTION_H
#define ROBOTACTION_H

#include "MotorDriver.h"

class robotAction {
    private:
    motorDriver MotorDriver;
    public:
    void forwards();
    void backwards();
    void left();
    void right();
};

#endif 