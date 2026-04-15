#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

enum Direction{BACKWARD, FORWARD};

class MotorDriver {
    private:
        int leftSpeed;
        int rightSpeed;
        Direction leftDirection;
        Direction rightDirection;
        bool isBraking;
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