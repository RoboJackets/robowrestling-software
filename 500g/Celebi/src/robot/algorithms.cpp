#include "robot/algorithms.hpp"

algorithmns :: algorithms(robot_actions *robot, world_state *world) {
    this -> robot = robot;
    this -> world = world;
}

algorithms :: forward_safe() {
    if (world_state -> line_check() != BOTH_ON) {
        drive_forward(5)
    }
}