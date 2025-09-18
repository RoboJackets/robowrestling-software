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
        void slam(EnemyPos enemyPos, OnLine onLine);
        void lineMovement(EnemyPos enemyPos, OnLine onLine);
}; 

#endif