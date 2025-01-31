#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

class MotorDriver {
private:
    int speed;
    int direction;
public:
    MotorDriver();
    void setSpeed(int speedValue);
    int getSpeed();
    void setDirection(int directionValue);
    int getDirection();
};

#endif