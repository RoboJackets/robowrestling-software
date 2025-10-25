#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

#include "Timer.hpp"

enum Direction{BACKWARD, FORWARD};

class MotorDriver {
    private:
        const int ACCELERATION_INTERVAL = 1;
        const int LEFT_DIRECTION_CHANGE_TIMER_DURATION = 40;
        const int RIGHT_DIRECTION_CHANGE_TIMER_DURATION = 40;
        int leftSpeed;
        int rightSpeed;
        int leftTargetSpeed;
        int rightTargetSpeed;
        Direction leftDirection;
        Direction rightDirection;
        Timer *acclerationTimer;
        Timer *leftDirectionTimer;
        Timer *rightDirectionTimer;
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