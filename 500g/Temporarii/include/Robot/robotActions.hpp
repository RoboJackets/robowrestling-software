#include "Robot/motorDriver.hpp"
#include "Enumerations/PrevAction.hpp"
#include "Enumerations/EnemyPositions.hpp"

#ifndef ROBOTACTIONS_HPP
#define ROBOTACTIONS_HPP 

class RobotActions {
    private: 
        MotorDriver *flDriver;
        MotorDriver *frDriver;
        MotorDriver *blDriver;
        MotorDriver *brDriver;
        int speed;
        
        PrevAction prev_action;
    public:
        RobotActions(MotorDriver *, MotorDriver *, MotorDriver *, MotorDriver *);
        void Attack(EnemyPositions pos);
        void Forward(int spd);
        void Backwards(int spd);
        void Left(int spd);
        void Right(int spd);
        void Circle();
};

#endif