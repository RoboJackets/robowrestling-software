#include "Sensors/WorldState.hpp"
#include "Robot/algorithm.hpp"

#ifndef ROBOTSTATE_HPP
#define ROBOTSTATE_HPP 

class RobotState {
    private: 
        WorldState *world;
        Algorithm *algo;
    public:
        RobotState(WorldState *world, Algorithm *algo);
        void runAlgorithm();
};

#endif