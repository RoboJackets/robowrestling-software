#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

class MotorDriver {
    private: 
        int speed;
        bool direction;
    public:
        int getSpeed();
        void setSpeed(int speed);
        bool getDirection();
        void setDirection(bool direction);
};

#endif // MOTORDRIVER_H
