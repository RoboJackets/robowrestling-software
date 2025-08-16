#ifndef BACKSPIN_H
#define BACKSPIN_H

#include "RobotAction.h"
#include "WorldState.h"
#include "utility/AutoTimer.hpp"

class BackSpin {
    private:
        RobotAction *robotAction;
        WorldState *worldState;
        AutoTimer *backup;
        AutoTimer *spin;
    public:
        BackSpin(WorldState *_worldState, RobotAction *_robotAction);
        void run();
};

#endif