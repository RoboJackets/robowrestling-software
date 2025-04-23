#include "robot/robot_state.hpp"

robot_state :: robot_state(world_state *worldState, algorithms *algorithm) {
    this -> worldState = worldState;
    this -> algorithm = algorithm;
    for (int i = 0; i < 5; i++) {
        this -> prev[i] = UNKNOWN;
    }
}

void robot_state :: runAlgorithm() {
    //line_states selfPosition = worldState -> line_check();
    //enemy_states enemyPosition = worldState -> enemy_pos(); 

    //Select algorithm based on position.
    //algorithm -> draw_seek();
    algorithm -> slammy_whammy();
}