#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "Timer.hpp"

enum Direction{BACKWARD, FORWARD};

class MotorDriver {
    private:
        int leftSpeed;
        int rightSpeed;
        Direction leftDirection;
        Direction rightDirection;
    public:
        MotorDriver();
        void setSpeed(int _leftSpeed, int _rightSpeed);
        void setDirection(Direction _leftDirection, Direction _rightDirection);
        int getLeftSpeed();
        int getRightSpeed();
        Direction getLeftDirection();
        Direction getRightDirection();
};

#endif