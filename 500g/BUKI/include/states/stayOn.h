#ifndef STAY_ON_H_
#define STAY_ON_H_

#include "action/robotAction.h"
#include "states/worldState.h"

class StayOn {
    private:
        RobotAction* robotAction;
        WorldState* worldState;
    public:
        StayOn(RobotAction* robotActionParameter, WorldState* worldState);     // constructor
        void runAlgorithm();
};

#endif