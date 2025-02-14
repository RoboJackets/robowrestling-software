#ifndef STAY_ON_H_
#define STAY_ON_H_

#include "states/robotState.h"
#include "action/robotAction.h"
#include "states/worldState.h"

class StayOn : public RobotState {         // Polymorphism (I have no idea what's going on here - Shahmeel)
    private:
        RobotAction* robotAction;
        WorldState* worldState;
    public:
        StayOn(RobotAction* robotActionParameter, WorldState* worldState);     // constructor
        void runAlgorithm();           // Override runAlgorithm() from RobotState
};

#endif