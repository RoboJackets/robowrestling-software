#include "include/ROBOT/MotorDriver.h"
#ifndef ROBOTACTION_H
#define ROBOTACTION_H

class RobotAction {
    private:
        MotorDriver leftMotorDriver;
        MotorDriver rightMotorDriver;

    public:
        void move(int lMSpeed, bool lMDir, int rMSpeed, bool rMDir);
        void moveForward();
        void moveBackward();
        void turnLeft();
        void turnRight();
        void stop();
};
#endif // ROBOTACTION_H