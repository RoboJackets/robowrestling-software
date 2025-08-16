#ifndef TURNAROUND_H
#define TURNAROUND_H

#include "RobotAction.h"
#include "WorldState.h"
#include "utility/AutoTimer.hpp"

class TurnAround {
    private:
        RobotAction *robotAction;
        WorldState *worldState;
        AutoTimer *leftTimer;
        AutoTimer *rightTimer;
        const int leftTimerLength = 400;
        const int rightTimerLength = 400;
    public:
        TurnAround(WorldState *_worldState, RobotAction *_robotAction);
        void TurnAroundLeft();
        void TurnAroundRight();
};

#endif