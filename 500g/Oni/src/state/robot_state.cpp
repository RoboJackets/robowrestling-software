#include "state/robot_state.h"
#include "enums/state_enums.h"

robot_state :: robot_state(world_state *worldState, algorithms *algorithm) {
    this -> worldState = worldState;
    this -> algorithm = algorithm;
}

void robot_state :: runAlgorithm() {
    SelfPosition selfPosition = worldState -> line_state();
    EnemyPosition enemyPosition = worldState -> enemy_location(); 

    //Select algorithm base on position.
    algorithm -> go_forward();
}