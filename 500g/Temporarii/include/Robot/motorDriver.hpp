#ifndef MOTORDRIVER_HPP 

#define MOTORDRIVER_HPP 

class MotorDriver {
    private: 
        bool direction;
        int speed;
    public:
        bool getDirection();
        int getSpeed();
        void setDirection(bool value);
        void setSpeed(int value);
};

#endif