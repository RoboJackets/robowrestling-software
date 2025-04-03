#include "robot/robot_state.hpp"

robot_state :: robot_state(world_state *worldState, algorithms *algorithm) {
    this -> worldState = worldState;
    this -> algorithm = algorithm;
}

void robot_state :: runAlgorithm() {
    line_states selfPosition = worldState -> line_check();
    enemy_states enemyPosition = worldState -> enemy_pos(); 

    //Select algorithm base on position.
    algorithm -> forward_safe();
}

