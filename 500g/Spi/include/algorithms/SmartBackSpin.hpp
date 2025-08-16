#ifndef SMARTBACKSPIN_H
#define SMARTBACKSPIN_H

#include "RobotAction.h"
#include "WorldState.h"
#include "algorithms/BackSpinLeft.hpp"
#include "algorithms/BackSpinRight.hpp"

class SmartBackSpin : public Action {
    private:
        BackSpinLeft *backSpinLeft;
        BackSpinRight *backSpinRight;
        RobotAction *robotAction;
        WorldState *worldState;
        Action *lastAction;
    protected:
        virtual void performAction() = 0;
        virtual void resetTimers() = 0;
    public:
        SmartBackSpin(WorldState *_worldState, RobotAction* _robotAction);
};

#endif