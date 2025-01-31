#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "world/world_state.hpp"
#include "robot_state.hpp"
#include "enums/world_enums.hpp"

class algorithms {
    private:
        robot_state* robot;
        world_state* world;

    public:
        algorithms(robot_actions* robot, world_state* world);

        dummy_algorithm()
};
#endif