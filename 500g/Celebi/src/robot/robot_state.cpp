#include "robot/robot_state.hpp"

robot_state :: robot_state(world_state *worldState, algorithms *algorithm, timer* thymer) {
    this -> worldState = worldState;
    this -> algorithm = algorithm;
    this -> thymer = thymer;
}

void robot_state :: runAlgorithm() {
    line_states selfPosition = worldState -> line_check();
    enemy_states enemyPosition = worldState -> enemy_pos(); 

    //Select algorithm base on position.
    //algorithm -> draw();
    //seek();
    algorithm -> turn_test();
}

void robot_state :: seek() {
    if (algorithm -> turn_towards() == 0) {
        algorithm -> forward_safe();
    }
}