#include "robot/algorithms.hpp"
#include "enums/world_enums.hpp"

algorithms :: algorithms(robot_actions *robot, world_state *world) {
    this -> robot = robot;
    this -> world = world;
}

void algorithms :: forward_safe() {
    if (world -> line_check() != BOTH_ON) {
        robot -> drive_forward(5);
    }
}