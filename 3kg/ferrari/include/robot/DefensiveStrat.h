// header for defensive strat
#include "robot/WorldState.h"\
#include "robot/RobotActions.h"

#ifndef DEF_STRAT_H
#define DEF_STRAT_H

class DefensiveStrat {
    private: 
    // Variables needed to run the defensive strategy
    WorldState *worldState;
    RobotActions*robotActions;
    public:
        DefensiveStrat(WorldState*worldState, RobotActions*robotActions);
        void watchingEnemy();
        void charge();
        void runAway();
        void fullThrottle();
};

#endif