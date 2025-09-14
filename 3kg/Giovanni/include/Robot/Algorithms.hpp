#include "Robot/RobotActions.hpp"
#include "Enumerations/EnemyPos.cpp"
#include "Enumerations/OnLine.cpp"

#ifndef Algorithms_hpp

#define Algorithms_hpp

class Algorithms {
    private:
        RobotActions *action;
    
    public:
        Algorithms(RobotActions *);
        // Add more algorithms below
        void slam(EnemyPos enemyPos, OnLine onLine);
}; 

#endif