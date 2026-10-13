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
        Timer *left_direction_timer;
        Timer *right_direction_timer;
        bool isBraking;
        const int DIRECTION_TIMER_DURATION = 50;
    public:
        MotorDriver();
        void setSpeed(int _leftSpeed, int _rightSpeed);
        void setDirection(Direction _leftDirection, Direction _rightDirection);
        void setIsBraking(bool _isBraking);
        bool getIsBraking();
        int getLeftSpeed();
        int getRightSpeed();
        Direction getLeftDirection();
        Direction getRightDirection();
};

#endif