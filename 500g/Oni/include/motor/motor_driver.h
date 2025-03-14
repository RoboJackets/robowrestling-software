#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

class MotorDriver {
    private: 
        int speed;
        int direction;
    public:
        MotorDriver();
        int getSpeed();
        void setSpeed(int speed);
        int getDirection();
        void setDirection(int direction);
};
#endif