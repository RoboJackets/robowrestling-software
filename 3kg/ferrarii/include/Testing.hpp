#ifndef TESTING_H
#define TESTING_H

#include "WorldState.hpp"
#include "RobotActions.hpp"
#include "Speeds.hpp"

class Testing {
    private:
        WorldState* worldState;
        RobotActions* robotActions;
        bool stopflag; 
    public:
        Testing(WorldState* _worldState, RobotActions* _robotActions);
        void run();
};

#endif