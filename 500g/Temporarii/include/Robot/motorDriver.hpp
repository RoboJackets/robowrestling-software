#ifndef MOTORDRIVER_HPP 

#define MOTORDRIVER_HPP 

class MotorDriver {
    private: 
        bool dir;
        double speed;
    public:
        bool getDirection();
        double getSpeed();
        void setDirection(bool direction);
        void setSpeed(double speed);
};

#endif