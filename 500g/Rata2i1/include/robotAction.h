

#ifndef robotAction_H
#define robotAction_H
#include "motorDriver.h"
class robotAction {
    private:
        motorDriver leftMotor;
        motorDriver rightMotor;
    public:
        robotAction(motorDriver *leftMotor, motorDriver *rightMotor);
        void moveForward(int speed);
        void moveBackward(int speed);
        void turnLeft(int speed);
        void turnRight(int speed);
        void stop();
};

#endif