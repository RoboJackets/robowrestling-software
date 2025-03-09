#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"
#include "world/world_state.hpp"

class algorithms;

class robot_state {
    private:
        world_state* worldState;
        algorithms* algorithm;
    public:
        robot_state(world_state *worldState, algorithms *algorithm);
        void runAlgorithm();
    

};
#endif