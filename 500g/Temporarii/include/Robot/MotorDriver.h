#ifndef MOTORDRIVER_HPP 

#define MOTORDRIVER_HPP 

class MotorDriver {
    private: 
        bool direction;
        int speed;
        int value;
    public:
        bool getDirection();
        int getSpeed();
        int getValue();
        void setDirection(bool value);
        void setSpeed(int value);
        void setValue(int value);
};

#endif