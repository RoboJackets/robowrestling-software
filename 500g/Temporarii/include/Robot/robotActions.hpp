#ifndef ROBOTACTIONS_HPP
#include "Robot/motorDriver.hpp"
#include "Enumerations/PrevAction.hpp"
#include "Enumerations/EnemyPositions.hpp"

#define ROBOTACTIONS_HPP 

class RobotActions {
    private: 
        MotorDriver *frontLeftDriver;
        MotorDriver *frontRightDriver;
        MotorDriver *backLeftDriver;
        MotorDriver *backRightDriver;
        int speed;
        PrevAction prev_action;
    public:
        RobotActions(MotorDriver *, MotorDriver *, MotorDriver *, MotorDriver *);
        void Forward(EnemyPositions pos);
        void Backwards();
        void Left();
        void Right();
        void Circle();
};

#endif