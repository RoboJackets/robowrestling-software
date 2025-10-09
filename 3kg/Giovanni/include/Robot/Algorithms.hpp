#include "Robot/RobotActions.hpp"
#include "Enumerations/EnemyPos.hpp"
#include "Enumerations/OnLine.hpp"

#ifndef Algorithms_hpp

#define Algorithms_hpp

class Algorithms {
    private:
        RobotActions *action;
    
    public:
        Algorithms(RobotActions *);
        // Add more algorithms below
        int slam(EnemyPos enemyPos, OnLine onLine);
        int lineMovement(EnemyPos enemyPos, OnLine onLine);
}; 

#endif