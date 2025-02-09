

#ifndef robotAction_H
#define robotAction_H
#include "motorDriver.h"
class robotAction {
    private:
        motorDriver *leftMotor;
        motorDriver *rightMotor;
    public:
        robotAction(motorDriver *leftMotor, motorDriver *rightMotor);
        void moveForward(int speed);
        void moveForwardFor(int speed, int time);
        void moveBackward(int speed);
        void moveBackwardFor(int speed, int time);
        void turnLeft(int speed);
        void turnLeftFor(int speed, int time);
        void turnRight(int speed);
        void turnRightFor(int speed, int time);
        void stop();
};

#endif