#ifndef DODGE_H
#define DODGE_H

#include "action/robotAction.h"
#include "states/worldState.h"

class Dodge {
    private:
        RobotAction* robotAction;
        WorldState* worldState;
    public:
        Dodge(RobotAction* robotActionParameter, WorldState* worldStateParameter);
        void performDodge();
};

#endif