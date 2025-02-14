#include "Sensors/WorldState.cpp"
#include "Robot/algorithm.hpp"
#ifndef ROBOTSTATE_HPP

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