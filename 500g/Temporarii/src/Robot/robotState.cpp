#include "Robot/robotState.hpp"
#include "Robot/algorithm.hpp"

// type | Class Name | function name
RobotState::RobotState(WorldState *state, Algorithm *algorithm) {
    worldState = state;
    this->algorithm = algorithm;
}
void RobotState::runAlgorithm() {
    // void State
    /*
    if (worldState->getEnemyPosition() == SEND) {
        algorithm->RunItDown();
    }
    */
    algorithm->RunItDown();

    
    algorithm->search();
}