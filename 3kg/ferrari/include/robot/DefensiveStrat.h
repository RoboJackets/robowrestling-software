// header for defensive strat
#include "robot/WorldState.h"

#ifndef DEF_STRAT_H
#define DEF_STRAT_H

class DefensiveStrat {
    private: 
    // Variables needed to run the defensive strategy
    WorldState *worldState;
    public:
        DefensiveStrat(WorldState*worldState);
        void watchingEnemy();
        void charge();
        void runAway();
        void fullThrottle();
};

#endif