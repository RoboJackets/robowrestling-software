#ifndef ROBOTACTION_H
#define ROBOTACTION_H

#include "MotorDriver.h"

class RobotAction {
public:
    // Constructor
    RobotAction(MotorDriver* motorDriver);

    // Movement methods
    void moveForward(int input);
    void moveLeft(int input);
    void moveRight(int input);
    void moveBack(int input);

private:
    MotorDriver* motorDriver;
};

#endif 
