#include "Robot/motorDriver.cpp"
#ifndef ROBOTACTIONS_HPP

#define ROBOTACTIONS_HPP 

class RobotActions {
    private: 
        MotorDriver *frontLeftDriver;
        MotorDriver *frontRightDriver;
        MotorDriver *backLeftDriver;
        MotorDriver *backRightDriver;
    public:
        RobotActions(MotorDriver *, MotorDriver *, MotorDriver *, MotorDriver *);
        void Forward();
        void Backwards();
        void Left();
        void Right();
};

#endif