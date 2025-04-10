#include "robot/robot_state.hpp"

robot_state :: robot_state(world_state *worldState, algorithms *algorithm, timer* thymer) {
    this -> worldState = worldState;
    this -> algorithm = algorithm;
    this -> thymer = thymer;
    for (int i = 0; i < 5; i++) {
        this -> prev[i] = UNKNOWN;
    }
}

void robot_state :: runAlgorithm() {
    //line_states selfPosition = worldState -> line_check();
    enemy_states enemyPosition = worldState -> enemy_pos(); 

    //Select algorithm based on position.
    if (enemyPosition != UNKNOWN) {
        seek();
    } else {
        algorithm -> draw();
    }
}

void robot_state :: seek() {
    if (algorithm -> turn_towards() == 0) {
        algorithm -> forward_safe();
    }
}