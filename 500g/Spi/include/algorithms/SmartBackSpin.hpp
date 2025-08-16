#ifndef SMARTBACKSPIN_H
#define SMARTBACKSPIN_H

#include "RobotAction.h"
#include "WorldState.h"
#include "algorithms/BackSpinLeft.hpp"
#include "algorithms/BackSpinRight.hpp"

class SmartBackSpin {
    private:
        BackSpinLeft *backSpinLeft;
        BackSpinRight *backSpinRight;
        RobotAction *robotAction;
        WorldState *worldState;
        Action *lastAction;
    public:
        SmartBackSpin(WorldState *_worldState, RobotAction* _robotAction);
        void run();
};

#endif