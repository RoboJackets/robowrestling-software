#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "worldState.h"
#include "robotAction.h"
#include "Timer.h"
#include "stateEnums.h"

class Strategies {
    private:
        worldState *state;
        int currentState;
        robotAction *robot;
        Timer *timer;
        
    public:
        Strategies(worldState *state, robotAction *robot, Timer *timer);
        Strategies(worldState *state, robotAction *robot);
        void test();
        void moveForward();
        void generalStrategy();
        void runAway();
};
#endif