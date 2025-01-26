#include "robot/robot_state.hpp"

#include "enums/world_enums.hpp"

robot_state :: robot_state(world_state *ws, algorithms algorithm) {
    this -> worldState = worldState;
    this -> algorithm = algorithm;
}

void robot_state :: runAlgorithm() {
    line_states selfPosition = worldState -> line_check; 
    enemy_states enemyPosition = worldState -> enemy_pos; 

    //Select algorithm base on position.
    if (selfPosition == LEFT_ON) {

    } else if (selfPosition == RIGHT_ON) {

    } else if (selfPosition == BOTH_ON) {

    } else {

    }

    
}

