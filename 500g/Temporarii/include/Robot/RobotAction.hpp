#include "Robot/motorDriver.cpp"
#ifndef ROBOTACTION_HPP

#define ROBOTACTION_HPP 

class RobotAction {
    private: 
        MotorDriver motorDriver;
    public:
        RobotAction(RobotAction *RobotAction);
        void Forward();
        void Backwards();
        void Left();
        void Right();
};

#endif