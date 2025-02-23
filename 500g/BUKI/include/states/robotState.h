#ifndef ROBOT_STATE_H_
#define ROBOT_STATE_H_

#include "states/worldState.h"
#include "states/stayOn.h"
#include "action/robotAction.h"

class RobotState {
    private:    
        WorldState* worldState;             // pointer to WorldState instance
        StayOn* stayOn;
        RobotAction* robotAction;
    public:
        RobotState();
        RobotState(WorldState* worldStateParameter, StayOn* stayOnParameter, RobotAction* robotActionParameter);
        void controlRobot();
};

#endif