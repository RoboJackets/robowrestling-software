#include "../../include/motor/motor_driver.h"
#ifndef ROBOTACTION_H
#define ROBOTACTION_H

class RobotAction {
    private:
        MotorDriver *leftMotorDriver;
        MotorDriver *rightMotorDriver;
    public:
        void smallForward();
        void medForward();
        void largeForward();
        void smallBack();
        void medBack();
        void largeBack();
        void smallLeft();
        void medLeft();
        void largeLeft();
        void smallRight();
        void medRight();
        void largeRight();
        void stop();
};
#endif