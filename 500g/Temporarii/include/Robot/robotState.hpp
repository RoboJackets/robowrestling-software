#ifndef ROBOTSTATE_HPP
#include "Sensors/WorldState.h"
#include "Robot/algorithm.hpp"


#define ROBOTSTATE_HPP 

class RobotState {
    private: 
        WorldState *worldState;
        Algorithm *algorithm;
    public:
        RobotState(WorldState *state, Algorithm *algorithm);
        void runAlgorithm();
};

#endif