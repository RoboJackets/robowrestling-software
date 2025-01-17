#ifndef ROBOT_ACTION_H_
#define ROBOT_ACTION_H_

#include "sensors/MotorDriver.h"

class RobotAction {
    private:
    
    public:
        RobotAction();
        void turnLeft(MotorDriver** motors);
        void turnRight(MotorDriver** motors);
        void go(MotorDriver** motors);
        void GOGOGO(MotorDriver** motors);
        void reverse(MotorDriver** motors);
};

#endif