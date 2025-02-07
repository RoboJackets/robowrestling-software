#ifndef ROBOT_STATE_H_
#define ROBOT_STATE_H_

#include "states/worldState.h"

class RobotState {
    private:    
        WorldState* worldState;             // pointer to WorldState instance
    public: 
        RobotState();
        void runAlgorithm();
};

#endif