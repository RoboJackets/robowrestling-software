#include "Sensors/WorldState.hpp"
#include "Robot/algorithm.hpp"
#include "Enumerations/OnLine.hpp"
#include "Enumerations/AlgoLogs.hpp"

#ifndef ROBOTSTATE_HPP
#define ROBOTSTATE_HPP 

class RobotState {
    private: 
        WorldState *world;
        Algorithm *algo;
        AlgoLogs prevAlgo;
        EnemyPositions enemyPrev;
    public:
        RobotState(WorldState *world, Algorithm *algo);
        void runAlgorithm();
};

#endif