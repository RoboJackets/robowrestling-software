#ifndef ROBOTSTATE_H
#define ROBOTSTATE_H

#include "WorldState.h"
#include "RobotActions.h"

class RobotState {
    private:
        WorldState *worldState;
        RobotActions *robotActions;

    public:
        RobotState(WorldState *worldStatePtr, RobotActions *robotActionsPtr);
        void calculateState();
};

#endif