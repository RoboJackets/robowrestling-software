#ifndef MOTORDRIVER_HPP 

#define MOTORDRIVER_HPP 

class MotorDriver {
    private: 
        int direction;
        int speed;
    public:
        MotorDriver();
        int getDirection();
        int getSpeed();
        void setDirection(int value);
        void setSpeed(int value);
};

#endif