#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H

#include "algorithms.hpp"

#include "world/world_state.hpp"

class robot_state {
    private:
        world_state* worldState;
        algorithms algorithm;
    public:
        robot_state(world_state *ws, algorithms algorithm);
        void runAlgorithm();
    

};
#endif