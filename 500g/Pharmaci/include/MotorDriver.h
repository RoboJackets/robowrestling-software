#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H

class MotorDriver {
    private: 
        bool direction;
        double speed;

    public: 
        MotorDriver();
        MotorDriver(double speed, bool direction);
        void setDirection(bool direction);
        void setSpeed(double speed);
        double getSpeed();
        bool getDirection();

        double getVelocity();
        
};

#endif