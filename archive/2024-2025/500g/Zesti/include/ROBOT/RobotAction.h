#include "Zesti/include/ROBOT/MotorDriver.h"
#ifndef ROBOTACTION_H
#define ROBOTACTION_H

class RobotAction {
    private:
        MotorDriver leftMotorDriver;
        MotorDriver rightMotorDriver;
    public:
        void moveForward();
        void moveBackward();
        void turnLeft();
        void turnRight();
        void stop();
};
#endif // ROBOTACTION_H