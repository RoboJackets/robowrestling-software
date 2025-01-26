#ifndef ROBOT_ACTION_H_
#define ROBOT_ACTION_H_

#include "sensors/MotorDriver.h"

class RobotAction {
    private:
        MotorDriver* leftMotor;     // pointers to left and right motor drivers
        MotorDriver* rightMotor;
    public:
        RobotAction(MotorDriver* leftMotorParameter, MotorDriver* rightMotorParameter);   // Constructor (creates specific instances of parameters)
        void turnLeft();
        void turnRight();
        void go();
        void GOGOGO();
        void reverse();
};

#endif