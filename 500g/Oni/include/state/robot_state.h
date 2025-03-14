#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include "algorithms.h"
#include "../enums/state_enums.h"
#include "state/world_state.h"

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