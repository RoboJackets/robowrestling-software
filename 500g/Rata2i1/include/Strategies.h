#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "worldState.h"
#include "robotAction.h"
#include "Timer.h"
#include "stateEnums.h"

class Strategies {
    private:
        worldState *state;
        robotAction *robot;
        Timer *timer;
        
    public:
        Strategies(worldState *state, robotAction *robot, Timer *timer);
        void test();
};
#endif