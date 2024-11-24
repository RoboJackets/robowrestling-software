#include "Robot/MotorDriver.cpp"
#ifndef ROBOTACTIONS_HPP

#define ROBOTACTIONS_HPP 

class RobotActions {
    private: 
        MotorDriver motorDriver;
    public:
        void Forward();
        void Backwards();
        void Left();
        void Right();
};

#endif